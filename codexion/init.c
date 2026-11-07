#include "codexion.h"

static int	allocate_memory(t_simulation *sim)
{
	int	n;

	n = sim->cfg.coders;
	sim->coders = malloc(sizeof(t_coder) * n);
	sim->busy = malloc(sizeof(int) * n);
	sim->released = malloc(sizeof(long long) * n);
	sim->heap = malloc(sizeof(t_request) * n);
	sim->temp = malloc(sizeof(t_request) * n);
	if (!sim->coders || !sim->busy || !sim->released
		|| !sim->heap || !sim->temp)
		return (0);
	memset(sim->coders, 0, sizeof(t_coder) * n);
	memset(sim->busy, 0, sizeof(int) * n);
	memset(sim->released, 0, sizeof(long long) * n);
	return (1);
}

int	init_simulation(t_simulation *sim, t_config cfg)
{
	int	i;

	memset(sim, 0, sizeof(t_simulation));
	sim->cfg = cfg;
	if (!allocate_memory(sim))
	{
		free(sim->coders);
		free(sim->busy);
		free(sim->released);
		free(sim->heap);
		free(sim->temp);
		return (0);
	}
	if (pthread_mutex_init(&sim->mutex, NULL) != 0)
	{
		free(sim->coders);
		free(sim->busy);
		free(sim->released);
		free(sim->heap);
		free(sim->temp);
		return (0);
	}
	if (pthread_cond_init(&sim->changed, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->mutex);
		free(sim->coders);
		free(sim->busy);
		free(sim->released);
		free(sim->heap);
		free(sim->temp);
		return (0);
	}
	sim->start = now_ms();
	i = 0;
	while (i < cfg.coders)
	{
		sim->coders[i].sim = sim;
		sim->coders[i].id = i;
		sim->coders[i].last_start = sim->start;
		sim->released[i] = sim->start - cfg.cooldown;
		i++;
	}
	return (1);
}

void	destroy_simulation(t_simulation *sim)
{
	free(sim->coders);
	free(sim->busy);
	free(sim->released);
	free(sim->heap);
	free(sim->temp);
	pthread_cond_destroy(&sim->changed);
	pthread_mutex_destroy(&sim->mutex);
}
