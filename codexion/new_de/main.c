#include "codexion.h"

int	main(int ac, char **av)
{
	t_sim		sim;
	pthread_t	monitor;
	// &sim: address of the simulation structure.
	// 0: fill the memory with zero.
	//- sizeof(sim): number of bytes occupied by the structure.
	memset(&sim, 0, sizeof(sim));
	if (parse_args(&sim, ac, av) != 0)
		return (1);

	sim.start_time = get_time_ms();

	if (init_sim(&sim) != 0)
		return (1);


	/* start coders */
	for (int i = 0; i < sim.n_coders; i++)
	{
		// give this coder access to the main simulation structure
		sim.coders[i].sim = &sim;
		// &sim.coders[i].thread	Where to store the thread ID
		// NULL	Use default thread attributes
		// coder_routine: function executed by the new thread
		// &sim.coders[i]: argument passed to that function
		if (pthread_create(&sim.coders[i].thread, NULL, coder_routine,
				&sim.coders[i]) != 0)
		{
			destroy_sim(&sim);
			return (1);
		}
	}
	/* start monitor */
	if (pthread_create(&monitor, NULL, monitor_routine, &sim) != 0)
	{
		destroy_sim(&sim);
		return (1);
	}

	/* wait for all coders */
	for (int i = 0; i < sim.n_coders; i++)
		// Null means you want the default thread attributes.
		pthread_join(sim.coders[i].thread, NULL);
	pthread_join(monitor, NULL);

	destroy_sim(&sim);
	return (0);
}