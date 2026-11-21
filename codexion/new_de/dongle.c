#include "codexion.h"

void	dongle_init(t_dongle *d, int id, int cooldown)
{
	d->id = id;
	d->available = 1;
	d->cooldown_until = 0;
	pthread_mutex_init(&d->mutex, NULL);
	pthread_cond_init(&d->cond, NULL);
	d->queue = NULL;
	d->q_size = 0;
	d->q_cap = 0;
	(void)cooldown;
}

void	dongle_destroy(t_dongle *d)
{
	pthread_mutex_destroy(&d->mutex);
	pthread_cond_destroy(&d->cond);
	free(d->queue);
}

/* ---------- min-heap on t_request ---------- */

static int	req_less(t_request *a, t_request *b, t_sched sched)
{
	if (sched == EDF)
	{
		if (a->deadline != b->deadline)
			return (a->deadline < b->deadline);
		return (a->seq < b->seq);	/* tie-break */
	}
	/* FIFO: pure arrival order */
	return (a->seq < b->seq);
}

static void	heap_swap(t_request *a, t_request *b)
{
	t_request	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	heap_push(t_dongle *d, t_request r, t_sched sched)
{
	if (d->q_size == d->q_cap)
	{
		d->q_cap = d->q_cap ? d->q_cap * 2 : 8;
		d->queue = realloc(d->queue, sizeof(t_request) * d->q_cap);
	}
	int i = d->q_size++;
	d->queue[i] = r;
	while (i > 0)
	{
		int p = (i - 1) / 2;
		if (req_less(&d->queue[i], &d->queue[p], sched))
		{
			heap_swap(&d->queue[i], &d->queue[p]);
			i = p;
		}
		else
			break ;
	}
}

static t_request	heap_pop(t_dongle *d, t_sched sched)
{
	t_request	top = d->queue[0];
	d->queue[0] = d->queue[--d->q_size];
	int i = 0;
	while (1)
	{
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if (l < d->q_size && req_less(&d->queue[l], &d->queue[smallest], sched))
			smallest = l;
		if (r < d->q_size && req_less(&d->queue[r], &d->queue[smallest], sched))
			smallest = r;
		if (smallest == i)
			break ;
		heap_swap(&d->queue[i], &d->queue[smallest]);
		i = smallest;
	}
	return (top);
}

/* ---------- public ---------- */

/*
 * Coder c requests this dongle. Blocks until granted.
 * Returns 1 if granted, 0 if simulation stopped.
 */
int	dongle_request(t_dongle *d, t_coder *c, t_sim *sim)
{
	t_request	req;

	pthread_mutex_lock(&d->mutex);

	/* register request */
	pthread_mutex_lock(&sim->state_mutex);
	req.coder = c;
	req.deadline = c->last_compile_start + sim->time_to_burnout;
	req.seq = sim->seq_counter++;
	pthread_mutex_unlock(&sim->state_mutex);
	heap_push(d, req, sim->scheduler);

	/* wait until: we are top of queue AND dongle available AND cooldown over */
	while (!sim_is_stopped(sim))
	{
		long long	now = get_time_ms();

		if (d->q_size > 0 && d->queue[0].coder == c
			&& d->available && now >= d->cooldown_until)
		{
			heap_pop(d, sim->scheduler);
			d->available = 0;
			pthread_mutex_unlock(&d->mutex);
			return (1);
		}
		/* compute wait time: if top but cooling, wake at cooldown end;
		   else just wait a short time */
		if (d->q_size > 0 && d->queue[0].coder == c
			&& d->available && now < d->cooldown_until)
		{
			struct timespec	ts;
			long long		wait = d->cooldown_until - now;
			struct timeval	tv;
			gettimeofday(&tv, NULL);
			ts.tv_sec = tv.tv_sec + (tv.tv_usec / 1000000 + wait / 1000);
			ts.tv_nsec = (tv.tv_usec % 1000000) * 1000 + (wait % 1000) * 1000000;
			while (ts.tv_nsec >= 1000000000L)
			{
				ts.tv_sec++;
				ts.tv_nsec -= 1000000000L;
			}
			pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
		}
		else
		{
			struct timespec	ts;
			struct timeval	tv;
			gettimeofday(&tv, NULL);
			ts.tv_sec = tv.tv_sec;
			ts.tv_nsec = (tv.tv_usec + 2000) * 1000; /* 2ms */
			while (ts.tv_nsec >= 1000000000L)
			{
				ts.tv_sec++;
				ts.tv_nsec -= 1000000000L;
			}
			pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
		}
	}
	/* stopped: remove our request if still queued (best effort: leave it) */
	pthread_mutex_unlock(&d->mutex);
	return (0);
}

void	dongle_release(t_dongle *d, t_sim *sim)
{
	pthread_mutex_lock(&d->mutex);
	d->available = 1;
	d->cooldown_until = get_time_ms() + sim->dongle_cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}