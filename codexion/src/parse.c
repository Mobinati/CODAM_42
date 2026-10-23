
int isthere_string(str  *arg)
{
    int i;

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
	int	i;

	i = 0;
	if(!str)
		return("ERROR: no args");
    if(isthere_string(str) == 1)
        return("ERROR: numeric arg has str in it");
	return(atoi(str));
}

int	parse_arguments(int	argc, char	**argv)
{
    t_config = []
	if (argc != 9)
		return("ERROR");
    i = 1;
    while(i<9)
    {
        if(isthere_string(argv[i]) == 1)
            return("ERROR: numeric arg is either negative or has str in it")
    }
	else
	{
		t_config[0] = atoi(argv[1]);
		t_config[1] = atoi(argv[2]);
		t_config[2] = atoi(argv[3]);
        t_config[3] = atoi(argv[4]);
        t_config[4] = atoi(argv[5]);
        t_config[5] = atoi(argv[6]);
        t_config[6] = atoi(argv[7]);
        t_config[7] = atoi(argv[8]);
        if (!(argv[8]) == "fifo" || argv[8] == "edf")
            return("ERROR FOR SCHEDUELER (either fifo or edf)");
        return(t_config);
	}
}