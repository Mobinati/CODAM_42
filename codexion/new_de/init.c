#include "codexion.h"

int	setup_workspace(t_sim *simulation)
{
	pthread_mutex_init(&simulation->log_mutex, NULL);
	pthread_mutex_init(&simulation->state_mutex, NULL);
	pthread_cond_init(&simulation->state_cond, NULL);

	simulation->coders = malloc(sizeof(t_coder) * simulation->n_coders);
	simulation->dongles = malloc(sizeof(t_dongle) * simulation->n_coders);
	if (!simulation->coders || !simulation->dongles)
		return (1);

	for (int i = 0; i < simulation->n_coders;)
	{
		memset(&simulation->coders[i], 0, sizeof(t_coder));
		simulation->coders[i].id = i + 1;
		simulation->coders[i].last_compile_start = simulation->start_time;
		i++;
	}
	for (int i = 0; i < simulation->n_coders; i++)
		prepare_dongle(&simulation->dongles[i], i + 1, simulation->dongle_cooldown);

	/* link dongles: coder i has left = dongle i, right = dongle (i+1)%n */
	for (int i = 0; i < simulation->n_coders;)
	{
		simulation->coders[i].left = &simulation->dongles[i];
		simulation->coders[i].right = &simulation->dongles[(i + 1) % simulation->n_coders];
		i++;
	}
	return (0);
}

void	cleanup_workspace(t_sim *simulation)
{
	if (simulation->dongles)
	{
		for (int i = 0; i < simulation->n_coders;)
		{
			dispose_dongle(&simulation->dongles[i]);
			i++;
		}
		free(simulation->dongles);
	}
	if (simulation->coders)
		free(simulation->coders);
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_cond_destroy(&simulation->state_cond);
}




// #include "codexion.h"

// int	init_sim(t_sim *sim)
// {
// 	pthread_mutex_init(&sim->log_mutex, NULL);
// 	pthread_mutex_init(&sim->state_mutex, NULL);
// 	pthread_cond_init(&sim->state_cond, NULL);

// 	sim->coders = malloc(sizeof(t_coder) * sim->n_coders);
// 	sim->dongles = malloc(sizeof(t_dongle) * sim->n_coders);
// 	if (!sim->coders || !sim->dongles)
// 		return (1);

// 	for (int i = 0; i < sim->n_coders)
// 	{
// 		memset(&sim->coders[i], 0, sizeof(t_coder));
// 		sim->coders[i].id = i + 1;
// 		sim->coders[i].last_compile_start = sim->start_time;
// 		i++;
// 	}
// 	for (int i = 0; i < sim->n_coders; i++)
// 		dongle_init(&sim->dongles[i], i + 1, sim->dongle_cooldown);

// 	/* link dongles: coder i has left = dongle i, right = dongle (i+1)%n */
// 	for (int i = 0; i < sim->n_coders)
// 	{
// 		sim->coders[i].left = &sim->dongles[i];
// 		sim->coders[i].right = &sim->dongles[(i + 1) % sim->n_coders];
// 		i++;
// 	}
// 	return (0);
// }

// void	destroy_sim(t_sim *sim)
// {
// 	if (sim->dongles)
// 	{
// 		for (int i = 0; i < sim->n_coders)
// 		{
// 			dongle_destroy(&sim->dongles[i]);
// 			i++;
// 		}
// 		free(sim->dongles);
// 	}
// 	if (sim->coders)
// 		free(sim->coders);
// 	pthread_mutex_destroy(&sim->log_mutex);
// 	pthread_mutex_destroy(&sim->state_mutex);
// 	pthread_cond_destroy(&sim->state_cond);
// }