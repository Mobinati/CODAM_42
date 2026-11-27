#include "codexion.h"

long long	clock_millis(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL);
}

void	pause_while_active(long long ms, t_sim *simulation)
{
	long long	end = clock_millis() + ms;

	while (clock_millis() < end)
	{
		if (has_simulation_ended(simulation))
			break ;
		usleep(500);
	}
}

void	print_event(t_sim *simulation, int coder_id, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&simulation->log_mutex);
	if (!simulation->stop)
	{
		timestamp = clock_millis() - simulation->start_time;
		printf("%lld %d %s\n", timestamp, coder_id, msg);
		fflush(stdout);
	}
	pthread_mutex_unlock(&simulation->log_mutex);
}

int	has_simulation_ended(t_sim *simulation)
{
	int	result;

	pthread_mutex_lock(&simulation->state_mutex);
	result = simulation->stop;
	pthread_mutex_unlock(&simulation->state_mutex);
	return (result);
}

void	end_simulation(t_sim *simulation)
{
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->stop = 1;
	pthread_cond_broadcast(&simulation->state_cond);
	pthread_mutex_unlock(&simulation->state_mutex);
}

// #include "codexion.h"

// long long	get_time_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
// }

// void	ft_usleep(long long ms, t_sim *sim)
// {
// 	long long	end = get_time_ms() + ms;

// 	while (get_time_ms() < end)
// 	{
// 		if (sim_is_stopped(sim))
// 			break ;
// 		usleep(500);
// 	}
// }

// void	log_state(t_sim *sim, int coder_id, const char *msg)
// {
// 	long long	ts;

// 	pthread_mutex_lock(&sim->log_mutex);
// 	if (!sim->stop)
// 	{
// 		ts = get_time_ms() - sim->start_time;
// 		printf("%lld %d %s\n", ts, coder_id, msg);
// 		fflush(stdout);
// 	}
// 	pthread_mutex_unlock(&sim->log_mutex);
// }

// int	sim_is_stopped(t_sim *sim)
// {
// 	int	ret;

// 	pthread_mutex_lock(&sim->state_mutex);
// 	ret = sim->stop;
// 	pthread_mutex_unlock(&sim->state_mutex);
// 	return (ret);
// }

// void	sim_stop(t_sim *sim)
// {
// 	pthread_mutex_lock(&sim->state_mutex);
// 	sim->stop = 1;
// 	pthread_cond_broadcast(&sim->state_cond);
// 	pthread_mutex_unlock(&sim->state_mutex);
// }