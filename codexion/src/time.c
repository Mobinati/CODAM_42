#include <sys/time.h>


long long	get_time_ms(void)
{
	struct	timeval	now;
	gettimeofday(&now, NULL);
	return((long long)now.tv_sec*1000 + now.tv_usec/1000);
}

long long	elapsed_ms(long long start_time)
{
	return(get_time_ms() - start_time);
}

void	sleep_ms(long long duration)
{
	if (duration>0)
		usleep(duration * 1000); 

}

void	sleep_until(long long time)
{
	long long	remaining;

	remaining = time - get_time_ms();
	if (remaining > 0)
		usleep(remaining * 1000);
}