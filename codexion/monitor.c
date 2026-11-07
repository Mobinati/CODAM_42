#include "codexion.h"

static int	all_finished(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->cfg.coders)
	{
		if (sim->coders[i].compiles < sim->cfg.required)
			return (0);
		i++;
	}
	return (1);
}

static int	check_burnout(t_simulation *sim, long long now)
{
	int	i;

	i = 0;
	while (i < sim->cfg.coders)
	{
		if (sim->coders[i].compiles < sim->cfg.required
			&& now - sim->coders[i].last_start >= sim->cfg.burnout)
		{
			log_line(sim, i, "burned out");
			return (1);
		}
		i++;
	}
	return (0);
}

static long long	nearest_deadline(t_simulation *sim)
{
	long long	next;
	long long	value;
	int			i;

	next = 0;
	i = 0;
	while (i < sim->cfg.coders)
	{
		if (sim->coders[i].compiles < sim->cfg.required)
		{
			value = sim->coders[i].last_start + sim->cfg.burnout;
			if (next == 0 || value < next)
				next = value;
		}
		i++;
	}
	return (next);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	long long		now;
	long long		next;
	struct timespec	ts;

	sim = (t_simulation *)arg;
	pthread_mutex_lock(&sim->mutex);
	while (!sim->stop)
	{
		now = now_ms();
		if (check_burnout(sim, now) || all_finished(sim))
		{
			sim->stop = 1;
			pthread_cond_broadcast(&sim->changed);
			break ;
		}
		next = nearest_deadline(sim);
		ts.tv_sec = next / 1000;
		ts.tv_nsec = (next % 1000) * 1000000;
		pthread_cond_timedwait(&sim->changed, &sim->mutex, &ts);
	}
	pthread_mutex_unlock(&sim->mutex);
	return (NULL);
}
