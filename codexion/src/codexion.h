#include <pthread.h>


typedef enum e_coder_state
{
    THINKING,
    WAITING,
    COMPILING,
    DEBUGGING,
    REFACTORING,
    BURNED_OUT
}   t_coder_state;

typedef struct s_coder
{
    int             id;
    pthread_t       thread;
    long long       last_compile_start;
    int             compile_count;
    t_coder_state	state;
}   t_coder;

typedef struct  s_dongle
{
    pthread_mutex_t mutex;
    int             availability;
    long long       last_release_time;
}   t_dongle;

typedef struct  s_simulation
{
    t_coder         *coders;
    t_dongle        *dongles;
    int             number_of_coders;
    int             number_of_dongles;
    pthread_mutex_t state_mutex;
    pthread_mutex_t log_mutex;
    pthread_cond_t  state_cond;
    int             stop;

}   t_simulation;

typedef struct s_config
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}	t_config;

int		init_coders(t_simulation *simulation);
int		init_dongles(t_simulation *simulation);
int		init_sync_objects(t_simulation *simulation);
int		init_simulation(t_simulation *simulation);
void	destroy_dongles(t_simulation *simulation);
void	destroy_sync_objects(t_simulation *simulation);
int	    parse_arguments(int argc, char **argv, t_config *config);