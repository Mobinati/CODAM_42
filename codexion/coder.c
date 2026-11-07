#include "codexion.h"

static void	start_compile(t_coder *coder)
{
	t_simulation	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->mutex);
	if (!sim->stop)
	{
		coder->last_start = now_ms();
		log_line(sim, coder->id, "is compiling");
	}
	pthread_mutex_unlock(&sim->mutex);
}

static void	finish_compile(t_coder *coder)
{
	t_simulation	*sim;

	sim = coder->sim;
	release_dongles(coder);
	pthread_mutex_lock(&sim->mutex);
	coder->compiles++;
	if (!sim->stop)
		log_line(sim, coder->id, "is debugging");
	pthread_cond_broadcast(&sim->changed);
	pthread_mutex_unlock(&sim->mutex);
}

static void	start_refactor(t_coder *coder)
{
	t_simulation	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->mutex);
	if (!sim->stop)
		log_line(sim, coder->id, "is refactoring");
	pthread_mutex_unlock(&sim->mutex);
}

void	*coder_routine(void *arg)
{
	t_coder		*coder;
	t_simulation	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	while (!is_stopped(sim) && coder->compiles < sim->cfg.required)
	{
		if (!request_dongles(coder))
			break ;
		start_compile(coder);
		wait_until(sim, coder->last_start + sim->cfg.compile);
		if (is_stopped(sim))
			break ;
		finish_compile(coder);
		wait_until(sim, now_ms() + sim->cfg.debug);
		if (is_stopped(sim))
			break ;
		start_refactor(coder);
		wait_until(sim, now_ms() + sim->cfg.refactor);
	}
	return (NULL);
}
