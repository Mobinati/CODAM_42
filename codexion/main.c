#include "codexion.h"

static void	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->created)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	pthread_join(sim->monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_config		cfg;
	t_simulation	sim;
	int				i;

	if (!parse_args(argc, argv, &cfg))
	{
		fprintf(stderr, "Usage: ./codexion number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown fifo|edf\n");
		return (1);
	}
	if (!init_simulation(&sim, cfg))
		return (fprintf(stderr, "Error: initialization failed\n"), 1);
	if (pthread_create(&sim.monitor, NULL, monitor_routine, &sim) != 0)
		return (destroy_simulation(&sim), 1);
	i = 0;
	while (i < cfg.coders)
	{
		if (pthread_create(&sim.coders[i].thread, NULL,
				coder_routine, &sim.coders[i]) != 0)
			break ;
		sim.created++;
		i++;
	}
	if (sim.created != cfg.coders)
	{
		pthread_mutex_lock(&sim.mutex);
		sim.stop = 1;
		pthread_cond_broadcast(&sim.changed);
		pthread_mutex_unlock(&sim.mutex);
	}
	join_threads(&sim);
	destroy_simulation(&sim);
	return (0);
}
