/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:18:44 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:18:47 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosopher.h"
#include "table.h"
#include "logs.h"

static int	monitor_philosophers(t_philosopher **philosophers);
static int	monitor_philosopher(t_philosopher *philosopher);

void	*run_monitoring(void *philosophers_ptr)
{
	t_philosopher	**philosophers;
	t_philosopher	*philosopher;

	philosophers = (t_philosopher **) philosophers_ptr;
	philosopher = *philosophers;
	if (philosopher == NULL)
		return (NULL);
	while (get_table_state(philosopher->table) == RUNNING)
	{
		monitor_philosophers(philosophers);
		usleep(500);
	}
	return (NULL);
}

static int	monitor_philosophers(t_philosopher **philosophers)
{
	t_philosopher	*philosopher;
	int				index;

	philosopher = philosophers[0];
	if (philosopher == NULL)
		return (0);
	index = 0;
	while (index < philosopher->table->number_of_philosophers)
	{
		if (monitor_philosopher(philosophers[index]) == 0)
			return (0);
		index++;
	}
	return (0);
}

static int	monitor_philosopher(t_philosopher *philosopher)
{
	if (get_time_in_ms() - get_last_meal(philosopher)
		> (size_t) philosopher->time_to_die)
	{
		set_table_state(philosopher->table, FINISH);
		print_log(philosopher, MSG_DIE);
		return (0);
	}
	if (get_number_of_philosophers_satisfied(philosopher->table)
		== philosopher->table->number_of_philosophers)
	{
		set_table_state(philosopher->table, FINISH);
		return (0);
	}
	return (1);
}
