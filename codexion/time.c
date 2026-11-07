#include "codexion.h"

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static struct timespec	to_timespec(long long milliseconds)
{
	struct timespec	ts;

	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	return (ts);
}

void	wait_until(t_simulation *sim, long long end)
{
	struct timespec	ts;

	pthread_mutex_lock(&sim->mutex);
	while (!sim->stop && now_ms() < end)
	{
		ts = to_timespec(end);
		pthread_cond_timedwait(&sim->changed, &sim->mutex, &ts);
	}
	pthread_mutex_unlock(&sim->mutex);
}

int	is_stopped(t_simulation *sim)
{
	int	result;

	pthread_mutex_lock(&sim->mutex);
	result = sim->stop;
	pthread_mutex_unlock(&sim->mutex);
	return (result);
}

void	log_line(t_simulation *sim, int id, char *message)
{
	printf("%lld %d %s\n", now_ms() - sim->start, id + 1, message);
}
