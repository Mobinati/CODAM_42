
#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc != 9)
	{
		printf("Usage: ./codexion number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown fifo|edf\n");
		return (1);
	}
	simulation.number_of_coders = atoi(argv[1]);
	if (simulation.number_of_coders <= 0)
	{
		printf("Error: number_of_coders must be positive.\n");
		return (1);
	}
	simulation.number_of_dongles = simulation.number_of_coders;
	simulation.coders = NULL;
	simulation.dongles = NULL;
	if (!init_simulation(&simulation))
	{
		printf("Error: simulation initialization failed.\n");
		return (1);
	}
	printf("Simulation initialization successful!\n");
	destroy_sync_objects(&simulation);
	destroy_dongles(&simulation);
	free(simulation.coders);
	simulation.coders = NULL;
	return (0);
}
