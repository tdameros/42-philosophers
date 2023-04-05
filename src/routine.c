/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:20:11 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:20:12 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosopher.h"
#include "time.h"
#include "logs.h"
#include "routine.h"

static int	sleep_philosopher(size_t ms, t_philosopher *philosopher);

void	*philosopher_routine(void *philosopher_ptr)
{
	t_philosopher	*philosopher;

	philosopher = philosopher_ptr;
	while (get_table_state(philosopher->table) == WAITING)
		usleep(100);
	set_last_meal(philosopher, philosopher->table->start_time_in_ms);
	print_log(philosopher, MSG_THINK);
	if (philosopher->id % 2 == 0)
		sleep_philosopher(philosopher->time_to_eat / 10, philosopher);
	while (get_table_state(philosopher->table) == RUNNING)
	{
		take_forks(philosopher);
		set_last_meal(philosopher, get_time_in_ms());
		philosopher->count_meal++;
		if (philosopher->count_meal == philosopher->max_meal)
			set_philosopher_satisfied(philosopher->table);
		print_log(philosopher, MSG_EAT);
		sleep_philosopher(philosopher->time_to_eat, philosopher);
		print_log(philosopher, MSG_SLEEP);
		put_forks(philosopher);
		sleep_philosopher(philosopher->time_to_sleep, philosopher);
		print_log(philosopher, MSG_THINK);
		usleep(100);
	}
	return (NULL);
}

void	*single_philosopher_routine(void *philosopher_ptr)
{
	t_philosopher	*philosopher;

	philosopher = philosopher_ptr;
	print_log(philosopher, MSG_FORK);
	sleep_philosopher(philosopher->time_to_die, philosopher);
	print_log(philosopher, MSG_DIE);
	return (NULL);
}

static int	sleep_philosopher(size_t ms, t_philosopher *philosopher)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	usleep(ms * 1000 * 0.9);
	while ((get_time_in_ms() - start_time) < ms
		&& get_table_state(philosopher->table) == RUNNING)
	{
		usleep(100);
	}
	return (0);
}
