#include "codexion.h"

static int	check_all_done(t_sim *sim)
{
	int	done = 1;

	pthread_mutex_lock(&sim->state_mutex);
	for (int i = 0; i < sim->n_coders; i++)
		if (!sim->coders[i].done)
			done = 0;
	pthread_mutex_unlock(&sim->state_mutex);
	return (done);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim = (t_sim *)arg;

	while (!sim_is_stopped(sim))
	{
		/* check completion */
		if (check_all_done(sim))
		{
			sim_stop(sim);
			break ;
		}

		/* check burnout for each coder */
		long long	now = get_time_ms();

		for (int i = 0; i < sim->n_coders; i++)
		{
			t_coder	*c = &sim->coders[i];
			long long	last;

			pthread_mutex_lock(&sim->state_mutex);
			last = c->last_compile_start;
			pthread_mutex_unlock(&sim->state_mutex);

			if (now - last >= sim->time_to_burnout)
			{
				/* coder i has burned out */
				pthread_mutex_lock(&sim->state_mutex);
				sim->stop = 1;
				pthread_mutex_unlock(&sim->state_mutex);

				log_state(sim, c->id, "burned out");
				pthread_mutex_lock(&sim->state_mutex);
				pthread_cond_broadcast(&sim->state_cond);
				pthread_mutex_unlock(&sim->state_mutex);
				return (NULL);
			}
		}

		/* sleep ~1ms but responsive to stop */
		usleep(500);
	}
	return (NULL);
}