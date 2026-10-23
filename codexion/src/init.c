#include <pthread.h>
#include <stdlib.h>


int	init_coders(t_simulation *simulation)
{
	int	i;

	simulation->coders = malloc(sizeof(t_coder) * simulation->number_of_coders);
	if (!simulation->coders)
		return(0);
	i = 0;
	while (i < simulation->number_of_coders)
	{
		simulation->coders[i].id = i + 1;
		simulation->coders[i].compile_count = 0;
		simulation->coders[i].last_compile_start = 0;
		i++;
	}
	return(1);

}

int init_dongles(t_simulation *simulation)
{
	int	i;

	simulation->dongles = malloc(sizeof(t_dongle) * simulation->number_of_dongles);
	if (!simulation->dongles)
		return(0);

	i = 0;
	while (i < simulation->number_of_dongles)
	{
		simulation->dongles[i].availability = 1;
		simulation->dongles[i].last_release_time = 0;
		if(pthread_mutex_init(&simulation->dongles[i].mutex, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&simulation->dongles[i].mutex);
			}
			free(simulation->dongles);
			simulation->dongles = NULL;
			return(0);
		}
		i++;
	}
	return(1);
}

int	init_sync_objects(t_simulation *simulation)
{
	if (pthread_mutex_init(&simulation->state_mutex, NULL) != 0)
		return(0);
	if (pthread_mutex_init(&simulation->log_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->state_mutex);
		return(0);
	}
	if (pthread_cond_init(&simulation->state_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->state_mutex);
		pthread_mutex_destroy(&simulation->log_mutex);
		return(0);
	}
	simulation->stop = 0;
	return(1);
}

int	init_simulation(t_simulation *simulation)
{
	if (!init_coders(simulation))
		return(0);
	if (!init_dongles(simulation))
	{
		free(simulation->coders);
		simulation->coders = NULL;
		return(0);
	}
	if (!init_sync_objects(simulation))
	{
		destroy_dongles(simulation);
		free(simulation->coders);
		simulation->coders = NULL;
		return(0);
	}
	return(1);
}

void destroy_dongles(t_simulation	*simulation)
{
	int	i;

	i = 0;
	while (i < simulation->number_of_dongles)
	{
		pthread_mutex_destroy(&simulation->dongles[i].mutex);
		i++;
	}
	free(simulation->dongles);
	simulation->dongles = NULL;
}

void destroy_sync_objects(t_simulation	*simulation)
{
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_cond_destroy(&simulation->state_cond);
}