#include "codexion.h"

static int	is_positive_int(const char *s)
{
	if (!s || !*s)
		return (0);
	for (int i = 0; s[i]; i++)
		if (s[i] < '0' || s[i] > '9')
			return (0);
	return (1);
}

int	parse_args(t_sim *sim, int ac, char **av)
{
	if (ac != 9)
	{
		fprintf(stderr, "Error: expected 8 arguments\n");
		return (1);
	}
	if (!is_positive_int(av[1]) || !is_positive_int(av[2])
		|| !is_positive_int(av[3]) || !is_positive_int(av[4])
		|| !is_positive_int(av[5]) || !is_positive_int(av[6])
		|| !is_positive_int(av[7]))
	{
		fprintf(stderr, "Error: invalid numeric argument\n");
		return (1);
	}
	sim->n_coders = atoi(av[1]);
	sim->time_to_burnout = atoi(av[2]);
	sim->time_to_compile = atoi(av[3]);
	sim->time_to_debug = atoi(av[4]);
	sim->time_to_refactor = atoi(av[5]);
	sim->compiles_required = atoi(av[6]);
	sim->dongle_cooldown = atoi(av[7]);

	if (sim->n_coders < 1)
	{
		fprintf(stderr, "Error: need at least 1 coder\n");
		return (1);
	}
	if (strcmp(av[8], "fifo") == 0)
		sim->scheduler = FIFO;
	else if (strcmp(av[8], "edf") == 0)
		sim->scheduler = EDF;
	else
	{
		fprintf(stderr, "Error: scheduler must be fifo or edf\n");
		return (1);
	}
	return (0);
}