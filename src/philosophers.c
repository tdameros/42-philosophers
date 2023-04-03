/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:19:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:20:04 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <string.h>

#include "philosopher.h"
#include "routine.h"
#include "time.h"

t_philosopher	**initialize_philosophers(t_table *table, char **argv)
{
	t_philosopher	**philosophers;
	int				index;

	index = 0;
	philosophers = malloc(sizeof(*philosophers)
			* (table->number_of_philosophers + 1));
	if (philosophers == NULL)
		return (NULL);
	memset(philosophers, 0, sizeof(*philosophers)
		* (table->number_of_philosophers + 1));
	while (index < table->number_of_philosophers)
	{
		philosophers[index] = initialize_philosopher(index + 1, argv, table);
		if (philosophers[index] == NULL)
			return (free_philosophers(philosophers), NULL);
		index++;
	}
	return (philosophers);
}

void	free_philosophers(t_philosopher **philosophers)
{
	int	index;

	index = 0;
	while (philosophers[index] != NULL)
	{
		pthread_mutex_destroy(&philosophers[index]->last_meal_mutex);
		free(philosophers[index]);
		index++;
	}
	free(philosophers);
}

int	run_philosophers(t_philosopher **philosophers, t_table *table)
{
	int			index;
	pthread_t	monitor;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_create(table->threads + index, NULL,
				&philosopher_routine, philosophers[index]) != 0)
			return (-1);
		index++;
	}
	table->start_time_in_ms = get_time_in_ms();
	set_table_state(table, RUNNING);
	if (pthread_create(&monitor, NULL, run_monitoring, philosophers) != 0)
		return (-1);
	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_join(table->threads[index], NULL) != 0)
			return (-1);
		index++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (-1);
	return (0);
}

int	run_philosopher(t_philosopher **philosophers, t_table *table)
{
	int	index;

	index = 0;
	set_table_state(table, RUNNING);
	if (pthread_create(table->threads + index, NULL,
			&single_philosopher_routine, philosophers[index]) != 0)
		return (-1);
	if (pthread_join(table->threads[index], NULL) != 0)
		return (-1);
	return (0);
}
