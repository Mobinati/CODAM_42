#include "codexion.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	read_number(char *str, int *number)
{
	long	value;
	int		i;

	if (!is_number(str))
		return (0);
	value = 0;
	i = 0;
	while (str[i])
	{
		value = value * 10 + str[i] - '0';
		if (value > INT_MAX)
			return (0);
		i++;
	}
	*number = atoi(str);
	return (1);
}

int	parse_args(int argc, char **argv, t_config *cfg)
{
	int	*numbers;
	int	i;

	if (argc != 9)
		return (0);
	numbers = (int *)cfg;
	i = 0;
	while (i < 7)
	{
		if (!read_number(argv[i + 1], &numbers[i]))
			return (0);
		i++;
	}
	if (cfg->coders < 1 || cfg->burnout < 1 || cfg->compile < 1
		|| cfg->debug < 1 || cfg->refactor < 1 || cfg->required < 1
		|| cfg->cooldown < 0)
		return (0);
	if (strcmp(argv[8], "fifo") == 0)
		cfg->edf = 0;
	else if (strcmp(argv[8], "edf") == 0)
		cfg->edf = 1;
	else
		return (0);
	return (1);
}
