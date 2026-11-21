#include "codexion.h"

static int	take_two_dongles(t_coder *c, t_sim *sim)
{
	/*
	 * Lock ordering to prevent deadlock:
	 * always take the dongle with smaller id first (or, for 1 coder,
	 * just the single dongle).
	 */
	if (sim->n_coders == 1)
	{
		if (dongle_request(c->left, c, sim))
			log_state(sim, c->id, "has taken a dongle");
		return (0);
	}

	t_dongle	*first;
	t_dongle	*second;

	if (c->left->id < c->right->id)
	{
		first = c->left;
		second = c->right;
	}
	else
	{
		first = c->right;
		second = c->left;
	}

	if (!dongle_request(first, c, sim))
		return (0);
	log_state(sim, c->id, "has taken a dongle");

	if (!dongle_request(second, c, sim))
	{
		dongle_release(first, sim);
		return (0);
	}
	log_state(sim, c->id, "has taken a dongle");
	return (1);
}


static void	release_dongles(t_coder *c, t_sim *sim)
{
	dongle_release(c->right, sim);
	if (sim->n_coders > 1)
		dongle_release(c->left, sim);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;
	t_sim	*sim;

	c = (t_coder *)arg;
	sim = c->sim;

	/* Small stagger so logs look natural */
	if (c->id % 2 == 0)
		ft_usleep(1, sim);

	while (!sim_is_stopped(sim))
	{
		/* ---- compile phase ---- */
		if (!take_two_dongles(c, sim))
			break ;

		pthread_mutex_lock(&sim->state_mutex);
		c->last_compile_start = get_time_ms();
		pthread_mutex_unlock(&sim->state_mutex);

		log_state(sim, c->id, "is compiling");
		ft_usleep(sim->time_to_compile, sim);

		release_dongles(c, sim);

		pthread_mutex_lock(&sim->state_mutex);
		c->compile_count++;
		if (c->compile_count >= sim->compiles_required)
			c->done = 1;
		pthread_mutex_unlock(&sim->state_mutex);

		if (sim_is_stopped(sim))
			break ;

		/* Stop if required compilations are completed */
		if (c->done)
			break ;

		/* ---- debug phase ---- */
		log_state(sim, c->id, "is debugging");
		ft_usleep(sim->time_to_debug, sim);
		if (sim_is_stopped(sim))
			break ;

		/* ---- refactor phase ---- */
		log_state(sim, c->id, "is refactoring");
		ft_usleep(sim->time_to_refactor, sim);
		if (sim_is_stopped(sim))
			break ;
	}
	return (NULL);
}
