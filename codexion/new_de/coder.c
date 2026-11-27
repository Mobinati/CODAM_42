#include "codexion.h"

// static: bcs here we haven internal helper function, 
// this func is only accessible within this source file
static int	get_dongle_pair(t_coder *worker, t_sim *simulation)
{
	/*
	 removeing the circular resource-ordering condition that causes deadlock 
	 the order is in the way to prevent deadlock:
	  we always first take the dongle with smaller id first (or, for 1 coder,
	just the single dongle).
	 */
	if (simulation->n_coders == 1)
	{
		if (claim_dongle(worker->left, worker, simulation))
			print_event(simulation, worker->id, "has taken a dongle");
		return (0);
	}

	t_dongle	*first_dongle;
	t_dongle	*second_dongle;

	if (worker->left->id < worker->right->id)
	{
		first_dongle = worker->left;
		second_dongle = worker->right;
	}
	else
	{
		first_dongle = worker->right;
		second_dongle = worker->left;
	}

	if (!claim_dongle(first_dongle, worker, simulation))
		return (0);
	print_event(simulation, worker->id, "has taken a dongle");

	if (!claim_dongle(second_dongle, worker, simulation))
	{
		return_dongle(first_dongle, simulation);
		return (0);
	}
	print_event(simulation, worker->id, "has taken a dongle");
	return (1);
}


static void	put_dongle_pair(t_coder *worker, t_sim *simulation)
{
	return_dongle(worker->right, simulation);
	if (simulation->n_coders > 1)
		return_dongle(worker->left, simulation);
}

// later to be used in:
// pthread_create(&sim.coders[i].thread, NULL, coder_routine, &sim.coders[i]) != 0)
// here we have (void *) as its return type: 
// a generic pointer that can be returned when the thread finishes.
void	*coder_workflow(void *arg)
{
	t_coder	*worker;
	t_sim	*simulation;

	// re are converting the generic pointer void * into a t_coder *
	worker = (t_coder *)arg;

	// "sim = coder->sim" maening: I am a coder thread. I have a pointer to my own coder structure. 
	// Through that structure, I can reach the shared simulation.
	simulation = worker->sim;

	/* Small stagger so logs look natural */
	if (worker->id % 2 == 0)
		pause_while_active(1, simulation);

	while (!has_simulation_ended(simulation))
	{
		/* $$$$$$$  compileing phase $$$$$ */
		if (!get_dongle_pair(worker, simulation))
			break ;

		pthread_mutex_lock(&simulation->state_mutex);
		worker->last_compile_start = clock_millis();
		pthread_mutex_unlock(&simulation->state_mutex);

		print_event(simulation, worker->id, "is compiling");
		pause_while_active(simulation->time_to_compile, simulation);

		put_dongle_pair(worker, simulation);

		pthread_mutex_lock(&simulation->state_mutex);
		worker->compile_count++;
		if (worker->compile_count >= simulation->compiles_required)
			worker->done = 1;
		pthread_mutex_unlock(&simulation->state_mutex);

		if (has_simulation_ended(simulation))
			break ;

		/* Stop if required compilations are completed */
		if (worker->done)
			break ;

		/* ---- debuging phase -++++--- */
		print_event(simulation, worker->id, "is debugging");
		pause_while_active(simulation->time_to_debug, simulation);
		if (has_simulation_ended(simulation))
			break ;

		/* %%%% refactor phase %%%%%%% */
		print_event(simulation, worker->id, "is refactoring");
		pause_while_active(simulation->time_to_refactor, simulation);
		if (has_simulation_ended(simulation))
			break ;
	}
	return (NULL);
}



// #include "codexion.h"

// static int	get_resources(t_coder *worker, t_sim *simulation)
// {
// 	/*
// 	 * Lock ordering to prevent deadlock:
// 	 * always take the dongle with smaller id first (or, for 1 coder,
// 	 * just the single dongle).
// 	 */
// 	if (simulation->n_coders == 1)
// 	{
// 		if (dongle_request(worker->left, worker, simulation))
// 			log_state(simulation, worker->id, "has taken a dongle");
// 		return (0);
// 	}

// 	t_dongle	*lower;
// 	t_dongle	*upper;

// 	if (worker->left->id < worker->right->id)
// 	{
// 		lower = worker->left;
// 		upper = worker->right;
// 	}
// 	else
// 	{
// 		lower = worker->right;
// 		upper = worker->left;
// 	}

// 	if (!dongle_request(lower, worker, simulation))
// 		return (0);
// 	log_state(simulation, worker->id, "has taken a dongle");

// 	if (!dongle_request(upper, worker, simulation))
// 	{
// 		dongle_release(lower, simulation);
// 		return (0);
// 	}
// 	log_state(simulation, worker->id, "has taken a dongle");
// 	return (1);
// }


// static void	free_resources(t_coder *worker, t_sim *simulation)
// {
// 	dongle_release(worker->right, simulation);
// 	if (simulation->n_coders > 1)
// 		dongle_release(worker->left, simulation);
// }

// void	*run_coder(void *arg)
// {
// 	t_coder	*worker;
// 	t_sim	*simulation;
// 	// re are converting the generic pointer void * into a t_coder *
// 	worker = (t_coder *)arg;
// 	simulation = worker->sim;

// 	/* Small stagger so logs look natural */
// 	if (worker->id % 2 == 0)
// 		ft_usleep(1, simulation);

// 	while (!sim_is_stopped(simulation))
// 	{
// 		/* $$$$$$$  compileing phase $$$$$ */
// 		if (!get_resources(worker, simulation))
// 			break ;

// 		pthread_mutex_lock(&simulation->state_mutex);
// 		worker->last_compile_start = get_time_ms();
// 		pthread_mutex_unlock(&simulation->state_mutex);

// 		log_state(simulation, worker->id, "is compiling");
// 		ft_usleep(simulation->time_to_compile, simulation);

// 		free_resources(worker, simulation);

// 		pthread_mutex_lock(&simulation->state_mutex);
// 		worker->compile_count++;
// 		if (worker->compile_count >= simulation->compiles_required)
// 			worker->done = 1;
// 		pthread_mutex_unlock(&simulation->state_mutex);

// 		if (sim_is_stopped(simulation))
// 			break ;

// 		/* Stop if required compilations are completed */
// 		if (worker->done)
// 			break ;

// 		/* ---- debuging phase -++++--- */
// 		log_state(simulation, worker->id, "is debugging");
// 		ft_usleep(simulation->time_to_debug, simulation);
// 		if (sim_is_stopped(simulation))
// 			break ;

// 		/* %%%% refactor phase %%%%%%% */
// 		log_state(simulation, worker->id, "is refactoring");
// 		ft_usleep(simulation->time_to_refactor, simulation);
// 		if (sim_is_stopped(simulation))
// 			break ;
// 	}
// 	return (NULL);
// }



// // #include "codexion.h"

// // // static: bcs here we haven internal helper function, 
// // // this func is only accessible within this source file
// // static int	take_two_dongles(t_coder *c, t_sim *sim)
// // {
// // 	/*
// // 	 removeing the circular resource-ordering condition that causes deadlock 
// // 	 the order is in the way to prevent deadlock:
// // 	  we always first take the dongle with smaller id first (or, for 1 coder,
// // 	just the single dongle).
// // 	 */
// // 	if (sim->n_coders == 1)
// // 	{
// // 		if (dongle_request(c->left, c, sim))
// // 			log_state(sim, c->id, "has taken a dongle");
// // 		return (0);
// // 	}

// // 	t_dongle	*first;
// // 	t_dongle	*second;

// // 	if (c->left->id < c->right->id)
// // 	{
// // 		first = c->left;
// // 		second = c->right;
// // 	}
// // 	else
// // 	{
// // 		first = c->right;
// // 		second = c->left;
// // 	}

// // 	if (!dongle_request(first, c, sim))
// // 		return (0);
// // 	log_state(sim, c->id, "has taken a dongle");

// // 	if (!dongle_request(second, c, sim))
// // 	{
// // 		dongle_release(first, sim);
// // 		return (0);
// // 	}
// // 	log_state(sim, c->id, "has taken a dongle");
// // 	return (1);
// // }


// // static void	release_dongles(t_coder *c, t_sim *sim)
// // {
// // 	dongle_release(c->right, sim);
// // 	if (sim->n_coders > 1)
// // 		dongle_release(c->left, sim);
// // }

// // // later to be used in:
// // // pthread_create(&sim.coders[i].thread, NULL, coder_routine, &sim.coders[i]) != 0)
// // // here we have (void *) as its return type: 
// // // a generic pointer that can be returned when the thread finishes.
// // void	*coder_routine(void *arg)
// // {
// // 	t_coder	*coder;
// // 	t_sim	*sim;

// // 	// re are converting the generic pointer void * into a t_coder *
// // 	coder = (t_coder *)arg;
	
// // 	// "sim = coder->sim" maening: I am a coder thread. I have a pointer to my own coder structure. 
// // 	// Through that structure, I can reach the shared simulation.
// // 	sim = coder->sim;

// // 	/* Small stagger so logs look natural */
// // 	if (coder->id % 2 == 0)
// // 		ft_usleep(1, sim);

// // 	while (!sim_is_stopped(sim))
// // 	{
// // 		/* $$$$$$$  compileing phase $$$$$ */
// // 		if (!take_two_dongles(coder, sim))
// // 			break ;

// // 		pthread_mutex_lock(&sim->state_mutex);
// // 		coder->last_compile_start = get_time_ms();
// // 		pthread_mutex_unlock(&sim->state_mutex);

// // 		log_state(sim, coder->id, "is compiling");
// // 		ft_usleep(sim->time_to_compile, sim);

// // 		release_dongles(coder, sim);

// // 		pthread_mutex_lock(&sim->state_mutex);
// // 		coder->compile_count++;
// // 		if (coder->compile_count >= sim->compiles_required)
// // 			coder->done = 1;
// // 		pthread_mutex_unlock(&sim->state_mutex);

// // 		if (sim_is_stopped(sim))
// // 			break ;

// // 		/* Stop if required compilations are completed */
// // 		if (coder->done)
// // 			break ;

// // 		/* ---- debuging phase -++++--- */
// // 		log_state(sim, coder->id, "is debugging");
// // 		ft_usleep(sim->time_to_debug, sim);
// // 		if (sim_is_stopped(sim))
// // 			break ;

// // 		/* %%%% refactor phase %%%%%%% */
// // 		log_state(sim, coder->id, "is refactoring");
// // 		ft_usleep(sim->time_to_refactor, sim);
// // 		if (sim_is_stopped(sim))
// // 			break ;
// // 	}
// // 	return (NULL);
// // }
