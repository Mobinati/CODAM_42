#include <stdlib.h>
#include <string.h>
#include "codexion.h"

int isthere_string(char  *arg)
{
    int i;

    if(!arg || !arg[0])
        return(1);
    i = 0;
    while(arg[i])
    {
        if(!(arg[i] >= '0' && arg[i] <= '9'))
            return(1);
        i++;
    }
    return(0);
}

int	parse_convert_str_to_int(char	*str)
{

	if(!str)
		return(0);
    if(isthere_string(str) == 1)
        return(0);
	return(atoi(str));
}

int	parse_arguments(int argc, char **argv, t_config *config)
{
    int i;

	if (argc != 9)
		return(0);
    i = 1;
    while(i<8)
    {
        if(isthere_string(argv[i]) == 1)
            return(0);
        i++;
    }
    if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
        return(0);

    config->number_of_coders = atoi(argv[1]);
    config->time_to_burnout = atoi(argv[2]);
    config->time_to_compile = atoi(argv[3]);
    config->time_to_debug = atoi(argv[4]);
    config->time_to_refactor = atoi(argv[5]);
    config->number_of_compiles_required = atoi(argv[6]);
    config->dongle_cooldown = atoi(argv[7]);
    config->schedueler = argv[8];

    if (config->number_of_coders <= 0
        || config->time_to_burnout <= 0
        || config->time_to_compile <= 0
        || config->time_to_debug <= 0
        || config->time_to_refactor <= 0
        || config->number_of_compiles_required <= 0
        || config->dongle_cooldown < 0)
	    return (0);
    return(1);
}