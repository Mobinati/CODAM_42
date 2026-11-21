#include "codexion.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

void	ft_usleep(long long ms, t_sim *sim)
{
	long long	end = get_time_ms() + ms;

	while (get_time_ms() < end)
	{
		if (sim_is_stopped(sim))
			break ;
		usleep(500);
	}
}

void	log_state(t_sim *sim, int coder_id, const char *msg)
{
	long long	ts;

	pthread_mutex_lock(&sim->log_mutex);
	if (!sim->stop)
	{
		ts = get_time_ms() - sim->start_time;
		printf("%lld %d %s\n", ts, coder_id, msg);
		fflush(stdout);
	}
	pthread_mutex_unlock(&sim->log_mutex);
}

int	sim_is_stopped(t_sim *sim)
{
	int	ret;

	pthread_mutex_lock(&sim->state_mutex);
	ret = sim->stop;
	pthread_mutex_unlock(&sim->state_mutex);
	return (ret);
}

void	sim_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->stop = 1;
	pthread_cond_broadcast(&sim->state_cond);
	pthread_mutex_unlock(&sim->state_mutex);
}