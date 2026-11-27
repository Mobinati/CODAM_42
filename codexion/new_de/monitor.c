#include "codexion.h"

static int	all_workers_finished(t_sim *simulation)
{
	int	finished = 1;

	pthread_mutex_lock(&simulation->state_mutex);
	for (int i = 0; i < simulation->n_coders; i++)
		if (!simulation->coders[i].done)
			finished = 0;
	pthread_mutex_unlock(&simulation->state_mutex);
	return (finished);
}

void	*watch_simulation(void *arg)
{
	t_sim	*simulation = (t_sim *)arg;

	while (!has_simulation_ended(simulation))
	{
		/* check completion */
		if (all_workers_finished(simulation))
		{
			end_simulation(simulation);
			break ;
		}

		/* check burnout for each coder */
		long long	current_time = clock_millis();

		for (int i = 0; i < simulation->n_coders;)
		{
			t_coder	*worker = &simulation->coders[i];
			long long	last;

			pthread_mutex_lock(&simulation->state_mutex);
			last = worker->last_compile_start;
			pthread_mutex_unlock(&simulation->state_mutex);

			if (current_time - last >= simulation->time_to_burnout)
			{
				/* coder i has burned out */
				pthread_mutex_lock(&simulation->state_mutex);
				simulation->stop = 1;
				pthread_mutex_unlock(&simulation->state_mutex);

				print_event(simulation, worker->id, "burned out");
				pthread_mutex_lock(&simulation->state_mutex);
				pthread_cond_broadcast(&simulation->state_cond);
				pthread_mutex_unlock(&simulation->state_mutex);
				return (NULL);
			}
			i++;
		}

		/* sleep ~1ms but responsive to stop */
		usleep(500);
	}
	return (NULL);
}


// #include "codexion.h"

// static int	check_all_done(t_sim *sim)
// {
// 	int	done = 1;

// 	pthread_mutex_lock(&sim->state_mutex);
// 	for (int i = 0; i < sim->n_coders; i++)
// 		if (!sim->coders[i].done)
// 			done = 0;
// 	pthread_mutex_unlock(&sim->state_mutex);
// 	return (done);
// }

// void	*monitor_routine(void *arg)
// {
// 	t_sim	*sim = (t_sim *)arg;

// 	while (!sim_is_stopped(sim))
// 	{
// 		/* check completion */
// 		if (check_all_done(sim))
// 		{
// 			sim_stop(sim);
// 			break ;
// 		}

// 		/* check burnout for each coder */
// 		long long	now = get_time_ms();

// 		for (int i = 0; i < sim->n_coders)
// 		{
// 			t_coder	*c = &sim->coders[i];
// 			long long	last;

// 			pthread_mutex_lock(&sim->state_mutex);
// 			last = c->last_compile_start;
// 			pthread_mutex_unlock(&sim->state_mutex);

// 			if (now - last >= sim->time_to_burnout)
// 			{
// 				/* coder i has burned out */
// 				pthread_mutex_lock(&sim->state_mutex);
// 				sim->stop = 1;
// 				pthread_mutex_unlock(&sim->state_mutex);

// 				log_state(sim, c->id, "burned out");
// 				pthread_mutex_lock(&sim->state_mutex);
// 				pthread_cond_broadcast(&sim->state_cond);
// 				pthread_mutex_unlock(&sim->state_mutex);
// 				return (NULL);
// 			}
// 			i++;
// 		}

// 		/* sleep ~1ms but responsive to stop */
// 		usleep(500);
// 	}
// 	return (NULL);
// }