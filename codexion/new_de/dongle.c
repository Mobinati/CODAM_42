#include "codexion.h"

void	prepare_dongle(t_dongle *dongle, int id, int cooldown)
{
	dongle->id = id;
	dongle->available = 1;
	dongle->cooldown_until = 0;
	pthread_mutex_init(&dongle->mutex, NULL);
	pthread_cond_init(&dongle->cond, NULL);
	dongle->queue = NULL;
	dongle->q_size = 0;
	dongle->q_cap = 0;
	(void)cooldown;
}

void	dispose_dongle(t_dongle *dongle)
{
	pthread_mutex_destroy(&dongle->mutex);
	pthread_cond_destroy(&dongle->cond);
	free(dongle->queue);
}

/* ---------- min-heap on t_request ---------- */

static int	request_precedes(t_request *first, t_request *second, t_sched scheduler)
{
	if (scheduler == EDF)
	{
		if (first->deadline != second->deadline)
			return (first->deadline < second->deadline);
		return (first->seq < second->seq);	/* tie-break */
	}
	/* FIFO: pure arrival order */
	return (first->seq < second->seq);
}

static void	exchange_requests(t_request *first, t_request *second)
{
	t_request	temporary = *first;
	*first = *second;
	*second = temporary;
}

static void	enqueue_request(t_dongle *dongle, t_request request, t_sched scheduler)
{
	if (dongle->q_size == dongle->q_cap)
	{
		dongle->q_cap = dongle->q_cap ? dongle->q_cap * 2 : 8;
		dongle->queue = realloc(dongle->queue, sizeof(t_request) * dongle->q_cap);
	}
	int index = dongle->q_size++;
	dongle->queue[index] = request;
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (request_precedes(&dongle->queue[index], &dongle->queue[parent], scheduler))
		{
			exchange_requests(&dongle->queue[index], &dongle->queue[parent]);
			index = parent;
		}
		else
			break ;
	}
}

static t_request	dequeue_request(t_dongle *dongle, t_sched scheduler)
{
	t_request	first_request = dongle->queue[0];
	dongle->queue[0] = dongle->queue[--dongle->q_size];
	int index = 0;
	while (1)
	{
		int left_child = 2 * index + 1;
		int right_child = 2 * index + 2;
		int smallest = index;
		if (left_child < dongle->q_size && request_precedes(&dongle->queue[left_child], &dongle->queue[smallest], scheduler))
			smallest = left_child;
		if (right_child < dongle->q_size && request_precedes(&dongle->queue[right_child], &dongle->queue[smallest], scheduler))
			smallest = right_child;
		if (smallest == index)
			break ;
		exchange_requests(&dongle->queue[index], &dongle->queue[smallest]);
		index = smallest;
	}
	return (first_request);
}

/* ---------- public ---------- */

/*
 * Coder c requests this dongle. Blocks until granted.
 * Returns 1 if granted, 0 if simulation stopped.
 */
int	claim_dongle(t_dongle *dongle, t_coder *worker, t_sim *simulation)
{
	t_request	request;

	pthread_mutex_lock(&dongle->mutex);

	/* register request */
	pthread_mutex_lock(&simulation->state_mutex);
	request.coder = worker;
	request.deadline = worker->last_compile_start + simulation->time_to_burnout;
	request.seq = simulation->seq_counter++;
	pthread_mutex_unlock(&simulation->state_mutex);
	enqueue_request(dongle, request, simulation->scheduler);

	/* wait until: we are top of queue AND dongle available AND cooldown over */
	while (!has_simulation_ended(simulation))
	{
		long long	current_time = clock_millis();

		if (dongle->q_size > 0 && dongle->queue[0].coder == worker
			&& dongle->available && current_time >= dongle->cooldown_until)
		{
			dequeue_request(dongle, simulation->scheduler);
			dongle->available = 0;
			pthread_mutex_unlock(&dongle->mutex);
			return (1);
		}
		/* compute wait time: if top but cooling, wake at cooldown end;
		   else just wait a short time */
		if (dongle->q_size > 0 && dongle->queue[0].coder == worker
			&& dongle->available && current_time < dongle->cooldown_until)
		{
			struct timespec	wait_time;
			long long		remaining = dongle->cooldown_until - current_time;
			struct timeval	current_tv;
			gettimeofday(&current_tv, NULL);
			wait_time.tv_sec = current_tv.tv_sec + (current_tv.tv_usec / 1000000 + remaining / 1000);
			wait_time.tv_nsec = (current_tv.tv_usec % 1000000) * 1000 + (remaining % 1000) * 1000000;
			while (wait_time.tv_nsec >= 1000000000L)
			{
				wait_time.tv_sec++;
				wait_time.tv_nsec -= 1000000000L;
			}
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &wait_time);
		}
		else
		{
			struct timespec	wait_time;
			struct timeval	current_tv;
			gettimeofday(&current_tv, NULL);
			wait_time.tv_sec = current_tv.tv_sec;
			wait_time.tv_nsec = (current_tv.tv_usec + 2000) * 1000; /* 2ms */
			while (wait_time.tv_nsec >= 1000000000L)
			{
				wait_time.tv_sec++;
				wait_time.tv_nsec -= 1000000000L;
			}
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &wait_time);
		}
	}
	/* stopped: remove our request if still queued (best effort: leave it) */
	pthread_mutex_unlock(&dongle->mutex);
	return (0);
}

void	return_dongle(t_dongle *dongle, t_sim *simulation)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->available = 1;
	dongle->cooldown_until = clock_millis() + simulation->dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}




// #include "codexion.h"

// void	dongle_init(t_dongle *d, int id, int cooldown)
// {
// 	d->id = id;
// 	d->available = 1;
// 	d->cooldown_until = 0;
// 	pthread_mutex_init(&d->mutex, NULL);
// 	pthread_cond_init(&d->cond, NULL);
// 	d->queue = NULL;
// 	d->q_size = 0;
// 	d->q_cap = 0;
// 	(void)cooldown;
// }

// void	dongle_destroy(t_dongle *d)
// {
// 	pthread_mutex_destroy(&d->mutex);
// 	pthread_cond_destroy(&d->cond);
// 	free(d->queue);
// }

// /* ---------- min-heap on t_request ---------- */

// static int	req_less(t_request *a, t_request *b, t_sched sched)
// {
// 	if (sched == EDF)
// 	{
// 		if (a->deadline != b->deadline)
// 			return (a->deadline < b->deadline);
// 		return (a->seq < b->seq);	/* tie-break */
// 	}
// 	/* FIFO: pure arrival order */
// 	return (a->seq < b->seq);
// }

// static void	heap_swap(t_request *a, t_request *b)
// {
// 	t_request	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// static void	heap_push(t_dongle *d, t_request r, t_sched sched)
// {
// 	if (d->q_size == d->q_cap)
// 	{
// 		d->q_cap = d->q_cap ? d->q_cap * 2 : 8;
// 		d->queue = realloc(d->queue, sizeof(t_request) * d->q_cap);
// 	}
// 	int i = d->q_size++;
// 	d->queue[i] = r;
// 	while (i > 0)
// 	{
// 		int p = (i - 1) / 2;
// 		if (req_less(&d->queue[i], &d->queue[p], sched))
// 		{
// 			heap_swap(&d->queue[i], &d->queue[p]);
// 			i = p;
// 		}
// 		else
// 			break ;
// 	}
// }

// static t_request	heap_pop(t_dongle *d, t_sched sched)
// {
// 	t_request	top = d->queue[0];
// 	d->queue[0] = d->queue[--d->q_size];
// 	int i = 0;
// 	while (1)
// 	{
// 		int l = 2 * i + 1;
// 		int r = 2 * i + 2;
// 		int smallest = i;
// 		if (l < d->q_size && req_less(&d->queue[l], &d->queue[smallest], sched))
// 			smallest = l;
// 		if (r < d->q_size && req_less(&d->queue[r], &d->queue[smallest], sched))
// 			smallest = r;
// 		if (smallest == i)
// 			break ;
// 		heap_swap(&d->queue[i], &d->queue[smallest]);
// 		i = smallest;
// 	}
// 	return (top);
// }

// /* ---------- public ---------- */

// /*
//  * Coder c requests this dongle. Blocks until granted.
//  * Returns 1 if granted, 0 if simulation stopped.
//  */
// int	dongle_request(t_dongle *d, t_coder *c, t_sim *sim)
// {
// 	t_request	req;

// 	pthread_mutex_lock(&d->mutex);

// 	/* register request */
// 	pthread_mutex_lock(&sim->state_mutex);
// 	req.coder = c;
// 	req.deadline = c->last_compile_start + sim->time_to_burnout;
// 	req.seq = sim->seq_counter++;
// 	pthread_mutex_unlock(&sim->state_mutex);
// 	heap_push(d, req, sim->scheduler);

// 	/* wait until: we are top of queue AND dongle available AND cooldown over */
// 	while (!sim_is_stopped(sim))
// 	{
// 		long long	now = get_time_ms();

// 		if (d->q_size > 0 && d->queue[0].coder == c
// 			&& d->available && now >= d->cooldown_until)
// 		{
// 			heap_pop(d, sim->scheduler);
// 			d->available = 0;
// 			pthread_mutex_unlock(&d->mutex);
// 			return (1);
// 		}
// 		/* compute wait time: if top but cooling, wake at cooldown end;
// 		   else just wait a short time */
// 		if (d->q_size > 0 && d->queue[0].coder == c
// 			&& d->available && now < d->cooldown_until)
// 		{
// 			struct timespec	ts;
// 			long long		wait = d->cooldown_until - now;
// 			struct timeval	tv;
// 			gettimeofday(&tv, NULL);
// 			ts.tv_sec = tv.tv_sec + (tv.tv_usec / 1000000 + wait / 1000);
// 			ts.tv_nsec = (tv.tv_usec % 1000000) * 1000 + (wait % 1000) * 1000000;
// 			while (ts.tv_nsec >= 1000000000L)
// 			{
// 				ts.tv_sec++;
// 				ts.tv_nsec -= 1000000000L;
// 			}
// 			pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
// 		}
// 		else
// 		{
// 			struct timespec	ts;
// 			struct timeval	tv;
// 			gettimeofday(&tv, NULL);
// 			ts.tv_sec = tv.tv_sec;
// 			ts.tv_nsec = (tv.tv_usec + 2000) * 1000; /* 2ms */
// 			while (ts.tv_nsec >= 1000000000L)
// 			{
// 				ts.tv_sec++;
// 				ts.tv_nsec -= 1000000000L;
// 			}
// 			pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
// 		}
// 	}
// 	/* stopped: remove our request if still queued (best effort: leave it) */
// 	pthread_mutex_unlock(&d->mutex);
// 	return (0);
// }

// void	dongle_release(t_dongle *d, t_sim *sim)
// {
// 	pthread_mutex_lock(&d->mutex);
// 	d->available = 1;
// 	d->cooldown_until = get_time_ms() + sim->dongle_cooldown;
// 	pthread_cond_broadcast(&d->cond);
// 	pthread_mutex_unlock(&d->mutex);
// }