#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_simulation t_simulation;

typedef struct s_config
{
	int				coders;
	int				burnout;
	int				compile;
	int				debug;
	int				refactor;
	int				required;
	int				cooldown;
	int				edf;
}	t_config;

typedef struct s_request
{
	int				coder_id;
	long long		deadline;
	unsigned long	order;
}	t_request;

typedef struct s_coder
{
	pthread_t		thread;
	t_simulation	*sim;
	int				id;
	int				compiles;
	int				waiting;
	int				granted;
	long long		last_start;
}	t_coder;

struct s_simulation
{
	t_config		cfg;
	t_coder			*coders;
	int				*busy;
	long long		*released;
	t_request		*heap;
	t_request		*temp;
	int				heap_size;
	unsigned long	next_order;
	pthread_mutex_t	mutex;
	pthread_cond_t	changed;
	pthread_t		monitor;
	long long		start;
	int				stop;
	int				created;
};

int			parse_args(int argc, char **argv, t_config *cfg);
int			init_simulation(t_simulation *sim, t_config cfg);
void		destroy_simulation(t_simulation *sim);
void		* coder_routine(void *arg);
void		* monitor_routine(void *arg);
long long	now_ms(void);
void		wait_until(t_simulation *sim, long long end);
void		log_line(t_simulation *sim, int id, char *message);
int			is_stopped(t_simulation *sim);
int			request_dongles(t_coder *coder);
void		release_dongles(t_coder *coder);
void		dispatch(t_simulation *sim);

#endif
