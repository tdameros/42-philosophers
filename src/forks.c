/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:19:23 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:19:24 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "philosopher.h"
#include "logs.h"

static int	take_left_fork(t_philosopher *philosopher);
static int	take_right_fork(t_philosopher *philosopher);
static int	put_left_fork(t_philosopher *philosopher);

int	take_forks(t_philosopher *philosopher)
{
	if (get_table_state(philosopher->table) == RUNNING)
		take_left_fork(philosopher);
	else
		return (0);
	if (get_table_state(philosopher->table) == RUNNING)
		take_right_fork(philosopher);
	else
		return (put_left_fork(philosopher));
	philosopher->take_forks = true;
	return (1);
}

static int	take_left_fork(t_philosopher *philosopher)
{
	int		index_fork;

	index_fork = get_index_left_fork(philosopher);
	pthread_mutex_lock(&philosopher->table->forks_mutex[index_fork]);
	print_log(philosopher, MSG_FORK);
	return (1);
}

static int	take_right_fork(t_philosopher *philosopher)
{
	int		index_fork;

	index_fork = get_index_right_fork(philosopher);
	pthread_mutex_lock(&philosopher->table->forks_mutex[index_fork]);
	print_log(philosopher, MSG_FORK);
	return (1);
}

static int	put_left_fork(t_philosopher *philosopher)
{
	int		index_fork;

	index_fork = get_index_left_fork(philosopher);
	pthread_mutex_unlock(&philosopher->table->forks_mutex[index_fork]);
	return (1);
}

int	put_forks(t_philosopher *philosopher)
{
	int		index_left_fork;
	int		index_right_fork;

	if (philosopher->take_forks == false)
		return (0);
	index_right_fork = get_index_right_fork(philosopher);
	index_left_fork = get_index_left_fork(philosopher);
	pthread_mutex_unlock(&philosopher->table->forks_mutex[index_left_fork]);
	pthread_mutex_unlock(&philosopher->table->forks_mutex[index_right_fork]);
	philosopher->take_forks = false;
	return (1);
}
