#include "codexion.h"

static int	before(t_simulation *sim, t_request a, t_request b)
{
	if (sim->cfg.edf && a.deadline != b.deadline)
		return (a.deadline < b.deadline);
	return (a.order < b.order);
}

static void	swap(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	push(t_simulation *sim, t_request request)
{
	int	i;

	i = sim->heap_size++;
	sim->heap[i] = request;
	while (i > 0 && before(sim, sim->heap[i],
			sim->heap[(i - 1) / 2]))
	{
		swap(&sim->heap[i], &sim->heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

static t_request	pop(t_simulation *sim)
{
	t_request	result;
	int			i;
	int			child;

	result = sim->heap[0];
	sim->heap_size--;
	sim->heap[0] = sim->heap[sim->heap_size];
	i = 0;
	while (2 * i + 1 < sim->heap_size)
	{
		child = 2 * i + 1;
		if (child + 1 < sim->heap_size
			&& before(sim, sim->heap[child + 1], sim->heap[child]))
			child++;
		if (!before(sim, sim->heap[child], sim->heap[i]))
			break ;
		swap(&sim->heap[i], &sim->heap[child]);
		i = child;
	}
	return (result);
}

static int	pair_free(t_simulation *sim, int id, long long now)
{
	int	left;
	int	right;

	left = id;
	right = (id + 1) % sim->cfg.coders;
	if (left == right || sim->busy[left] || sim->busy[right])
		return (0);
	if (now - sim->released[left] < sim->cfg.cooldown
		|| now - sim->released[right] < sim->cfg.cooldown)
		return (0);
	return (1);
}

static int	conflicts(t_simulation *sim, int id, t_request *blocked, int count)
{
	int	i;
	int	left;
	int	right;

	left = id;
	right = (id + 1) % sim->cfg.coders;
	i = 0;
	while (i < count)
	{
		if (blocked[i].coder_id == left || blocked[i].coder_id == right
			|| (blocked[i].coder_id + 1) % sim->cfg.coders == left
			|| (blocked[i].coder_id + 1) % sim->cfg.coders == right)
			return (1);
		i++;
	}
	return (0);
}

void	dispatch(t_simulation *sim)
{
	int			count;
	int			i;
	int			pending;
	long long	now;
	t_request	request;

	count = 0;
	i = 0;
	pending = sim->heap_size;
	now = now_ms();
	while (i < pending)
	{
		request = pop(sim);
		if (pair_free(sim, request.coder_id, now)
			&& !conflicts(sim, request.coder_id, sim->temp, count))
		{
			sim->busy[request.coder_id] = 1;
			sim->busy[(request.coder_id + 1) % sim->cfg.coders] = 1;
			sim->coders[request.coder_id].granted = 1;
			sim->coders[request.coder_id].waiting = 0;
			log_line(sim, request.coder_id, "has taken a dongle");
			log_line(sim, request.coder_id, "has taken a dongle");
		}
		else
			sim->temp[count++] = request;
		i++;
	}
	i = 0;
	while (i < count)
	{
		push(sim, sim->temp[i]);
		i++;
	}
	pthread_cond_broadcast(&sim->changed);
}

static long long	next_cooldown(t_simulation *sim)
{
	long long	next;
	long long	value;
	long long	now;
	int			i;

	next = 0;
	now = now_ms();
	i = 0;
	while (i < sim->cfg.coders)
	{
		if (!sim->busy[i])
		{
			value = sim->released[i] + sim->cfg.cooldown;
			if (value > now && (next == 0 || value < next))
				next = value;
		}
		i++;
	}
	return (next);
}

int	request_dongles(t_coder *coder)
{
	t_simulation	*sim;
	t_request		request;
	long long		wakeup;
	struct timespec	ts;

	sim = coder->sim;
	pthread_mutex_lock(&sim->mutex);
	coder->waiting = 1;
	request.coder_id = coder->id;
	request.deadline = coder->last_start + sim->cfg.burnout;
	request.order = sim->next_order++;
	push(sim, request);
	dispatch(sim);
	while (!sim->stop && !coder->granted)
	{
		wakeup = next_cooldown(sim);
		if (wakeup > now_ms())
		{
			ts.tv_sec = wakeup / 1000;
			ts.tv_nsec = (wakeup % 1000) * 1000000;
			pthread_cond_timedwait(&sim->changed, &sim->mutex, &ts);
		}
		else
			pthread_cond_wait(&sim->changed, &sim->mutex);
		dispatch(sim);
	}
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->mutex);
		return (0);
	}
	coder->granted = 0;
	pthread_mutex_unlock(&sim->mutex);
	return (1);
}

void	release_dongles(t_coder *coder)
{
	t_simulation	*sim;
	long long		now;

	sim = coder->sim;
	pthread_mutex_lock(&sim->mutex);
	now = now_ms();
	sim->busy[coder->id] = 0;
	sim->busy[(coder->id + 1) % sim->cfg.coders] = 0;
	sim->released[coder->id] = now;
	sim->released[(coder->id + 1) % sim->cfg.coders] = now;
	dispatch(sim);
	pthread_mutex_unlock(&sim->mutex);
}
