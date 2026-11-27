#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ---------- structs ---------- */

typedef struct s_dongle t_dongle;
typedef struct s_coder t_coder;
typedef struct s_sim t_sim;

typedef enum e_sched
{
	FIFO,
	EDF
}	t_sched;

typedef struct s_request
{
	t_coder	*coder;
	long long	deadline;	/* used for EDF */
	long long	seq;		/* used for FIFO tie-break / order */
}	t_request;

struct s_dongle
{
	int				id;
	int				available;		/* 1 if on table and not cooling */
	long long		cooldown_until;	/* ms */
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_request		*queue;			/* dynamic array of pending requests */
	int				q_size;
	int				q_cap;
};

struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	long long		last_compile_start;
	int				compile_count;
	int				done;			/* reached required compiles */
	t_sim			*sim;
};

struct s_sim
{
	int				n_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				compiles_required;
	int				dongle_cooldown;
	t_sched			scheduler;

	t_coder			*coders;
	t_dongle		*dongles;

	pthread_mutex_t	log_mutex;
	pthread_mutex_t	state_mutex;	/* protects stop flag & counts */
	pthread_cond_t	state_cond;

	int				stop;			/* simulation stop flag */
	int				all_done;		/* all coders reached required */
	long long		start_time;
	long long		seq_counter;	/* global FIFO ordering */
};

/* ---------- prototypes ---------- */

/* parsing.c */
int			read_config(t_sim *simulation, int ac, char **av);

/* init.c */
int			setup_workspace(t_sim *simulation);
void		cleanup_workspace(t_sim *simulation);

/* utils.c */
long long	clock_millis(void);
void		pause_while_active(long long ms, t_sim *simulation);
void		print_event(t_sim *simulation, int coder_id, const char *msg);
int			has_simulation_ended(t_sim *simulation);
void		end_simulation(t_sim *simulation);

/* dongle.c */
void		prepare_dongle(t_dongle *dongle, int id, int cooldown);
void		dispose_dongle(t_dongle *dongle);
int			claim_dongle(t_dongle *dongle, t_coder *worker, t_sim *simulation);
void		return_dongle(t_dongle *dongle, t_sim *simulation);

/* coder.c */
void		*coder_workflow(void *arg);

/* monitor.c */
void		*watch_simulation(void *arg);

#endif




// #ifndef CODEXION_H
// # define CODEXION_H

// # include <pthread.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <sys/time.h>
// # include <unistd.h>

// /* ---------- structs ---------- */

// typedef struct s_dongle t_dongle;
// typedef struct s_coder t_coder;
// typedef struct s_sim t_sim;

// typedef enum e_sched
// {
// 	FIFO,
// 	EDF
// }	t_sched;

// typedef struct s_request
// {
// 	t_coder	*coder;
// 	long long	deadline;	/* used for EDF */
// 	long long	seq;		/* used for FIFO tie-break / order */
// }	t_request;

// struct s_dongle
// {
// 	int				id;
// 	int				available;		/* 1 if on table and not cooling */
// 	long long		cooldown_until;	/* ms */
// 	pthread_mutex_t	mutex;
// 	pthread_cond_t	cond;
// 	t_request		*queue;			/* dynamic array of pending requests */
// 	int				q_size;
// 	int				q_cap;
// };

// struct s_coder
// {
// 	int				id;
// 	pthread_t		thread;
// 	t_dongle		*left;
// 	t_dongle		*right;
// 	long long		last_compile_start;
// 	int				compile_count;
// 	int				done;			/* reached required compiles */
// 	t_sim			*sim;
// };

// struct s_sim
// {
// 	int				n_coders;
// 	int				time_to_burnout;
// 	int				time_to_compile;
// 	int				time_to_debug;
// 	int				time_to_refactor;
// 	int				compiles_required;
// 	int				dongle_cooldown;
// 	t_sched			scheduler;

// 	t_coder			*coders;
// 	t_dongle		*dongles;

// 	pthread_mutex_t	log_mutex;
// 	pthread_mutex_t	state_mutex;	/* protects stop flag & counts */
// 	pthread_cond_t	state_cond;

// 	int				stop;			/* simulation stop flag */
// 	int				all_done;		/* all coders reached required */
// 	long long		start_time;
// 	long long		seq_counter;	/* global FIFO ordering */
// };

// /* ---------- prototypes ---------- */

// /* parsing.c */
// int			parse_args(t_sim *sim, int ac, char **av);

// /* init.c */
// int			init_sim(t_sim *sim);
// void		destroy_sim(t_sim *sim);

// /* utils.c */
// long long	get_time_ms(void);
// void		ft_usleep(long long ms, t_sim *sim);
// void		log_state(t_sim *sim, int coder_id, const char *msg);
// int			sim_is_stopped(t_sim *sim);
// void		sim_stop(t_sim *sim);

// /* dongle.c */
// void		dongle_init(t_dongle *d, int id, int cooldown);
// void		dongle_destroy(t_dongle *d);
// int			dongle_request(t_dongle *d, t_coder *c, t_sim *sim);
// void		dongle_release(t_dongle *d, t_sim *sim);

// /* coder.c */
// void	*run_coder(void *arg);

// /* monitor.c */
// void		*monitor_routine(void *arg);

// #endif