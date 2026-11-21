#include "codexion.h"

int	init_sim(t_sim *sim)
{
	pthread_mutex_init(&sim->log_mutex, NULL);
	pthread_mutex_init(&sim->state_mutex, NULL);
	pthread_cond_init(&sim->state_cond, NULL);

	sim->coders = malloc(sizeof(t_coder) * sim->n_coders);
	sim->dongles = malloc(sizeof(t_dongle) * sim->n_coders);
	if (!sim->coders || !sim->dongles)
		return (1);

	for (int i = 0; i < sim->n_coders; i++)
	{
		memset(&sim->coders[i], 0, sizeof(t_coder));
		sim->coders[i].id = i + 1;
		sim->coders[i].last_compile_start = sim->start_time;
	}
	for (int i = 0; i < sim->n_coders; i++)
		dongle_init(&sim->dongles[i], i + 1, sim->dongle_cooldown);

	/* link dongles: coder i has left = dongle i, right = dongle (i+1)%n */
	for (int i = 0; i < sim->n_coders; i++)
	{
		sim->coders[i].left = &sim->dongles[i];
		sim->coders[i].right = &sim->dongles[(i + 1) % sim->n_coders];
	}
	return (0);
}

void	destroy_sim(t_sim *sim)
{
	if (sim->dongles)
	{
		for (int i = 0; i < sim->n_coders; i++)
			dongle_destroy(&sim->dongles[i]);
		free(sim->dongles);
	}
	if (sim->coders)
		free(sim->coders);
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
	pthread_cond_destroy(&sim->state_cond);
}