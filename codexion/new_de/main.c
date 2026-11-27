#include "codexion.h"

int	main(int ac, char **av)
{
	t_sim		simulation;
	pthread_t	monitor;

	// &sim: address of the simulation structure.
	// 0: fill the memory with zero.
	//- sizeof(sim): number of bytes occupied by the structure.
	memset(&simulation, 0, sizeof(simulation));
	if (read_config(&simulation, ac, av) != 0)
		return (1);

	simulation.start_time = clock_millis();

	if (setup_workspace(&simulation) != 0)
		return (1);


	/* start coders */
	for (int i = 0; i < simulation.n_coders;)
	{
		// give this coder access to the main simulation structure
		simulation.coders[i].sim = &simulation;
		// &sim.coders[i].thread	Where to store the thread ID
		// NULL	Use default thread attributes
		// coder_routine: function executed by the new thread
		// &sim.coders[i]: argument passed to that function
		if (pthread_create(&simulation.coders[i].thread, NULL, coder_workflow,
				&simulation.coders[i]) != 0)
		{
			cleanup_workspace(&simulation);
			return (1);
		}
		i++;
	}
	/* start monitor */
	if (pthread_create(&monitor, NULL, watch_simulation, &simulation) != 0)
	{
		cleanup_workspace(&simulation);
		return (1);
	}

	/* wait for all coders */
	for (int i = 0; i < simulation.n_coders; i++)
		// Null means you want the default thread attributes.
		// general form: pthread_join(thread_id, return_value);
		// 1-thread has finished before cleaning up shared memory,
		// 2-collect the thread's termination status; 
		// 3-release resources associated with a joinable thread
		pthread_join(simulation.coders[i].thread, NULL);
	// monitor is also a thread, main thread should wait for the monitor to finish too
	pthread_join(monitor, NULL);

	cleanup_workspace(&simulation);
	return (0);
}

// #include "codexion.h"

// int	main(int ac, char **av)
// {
// 	t_sim		sim;
// 	pthread_t	monitor;

// 	memset(&sim, 0, sizeof(sim));
// 	if (parse_args(&sim, ac, av) != 0)
// 		return (1);

// 	sim.start_time = get_time_ms();

// 	if (init_sim(&sim) != 0)
// 		return (1);


// 	/* start coders */
// 	for (int i = 0; i < sim.n_coders; i++)
// 	{
// 		sim.coders[i].sim = &sim;
// 		if (pthread_create(&sim.coders[i].thread, NULL, coder_thread_work,
// 				&sim.coders[i]) != 0)
// 		{
// 			destroy_sim(&sim);
// 			return (1);
// 		}
// 	}
// 	/* start monitor */
// 	if (pthread_create(&monitor, NULL, monitor_routine, &sim) != 0)
// 	{
// 		destroy_sim(&sim);
// 		return (1);
// 	}

// 	/* wait for all coders */
// 	for (int i = 0; i < sim.n_coders; i++)
// 		pthread_join(sim.coders[i].thread, NULL);
// 	pthread_join(monitor, NULL);

// 	destroy_sim(&sim);
// 	return (0);
// }