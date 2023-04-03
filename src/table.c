/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:46:52 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/18 16:46:52 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <pthread.h>

#include "philosopher.h"
#include "time.h"

static int	initialize_mutex_in_table(t_table *table);

t_table	*initialize_table(size_t number_of_philosophers)
{
	t_table	*table;

	table = malloc(sizeof(*table));
	if (table == NULL)
		return (NULL);
	memset(table, 0, sizeof(*table));
	table->number_of_philosophers = number_of_philosophers;
	table->number_of_philosophers_satisfied = 0;
	table->state = WAITING;
	table->forks_mutex = malloc(sizeof(*table->forks_mutex)
			* number_of_philosophers);
	if (table->forks_mutex == NULL)
		return (free_table(table), NULL);
	if (initialize_mutex_in_table(table) < 0)
		return (free_table(table), NULL);
	table->threads = malloc(sizeof(*table->threads) * number_of_philosophers);
	if (table->threads == NULL)
		return (free_table(table), NULL);
	table->start_time_in_ms = get_time_in_ms();
	return (table);
}

void	free_table(t_table *table)
{
	int	index;

	if (table->forks_mutex == NULL)
		return ;
	index = 0;
	while (index < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks_mutex[index]);
		index++;
	}
	pthread_mutex_destroy(&table->state_mutex);
	pthread_mutex_destroy(&table->logs_mutex);
	pthread_mutex_destroy(&table->number_of_philosophers_satisfied_mutex);
	free(table->forks_mutex);
	free(table->threads);
	free(table);
}

static int	initialize_mutex_in_table(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks_mutex[index], NULL) != 0)
			return (-1);
		index++;
	}
	if (pthread_mutex_init(&table->number_of_philosophers_satisfied_mutex,
			NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&table->logs_mutex, NULL) != 0)
		return (-1);
	return (0);
}

t_state	get_table_state(t_table *table)
{
	enum e_state	state;

	pthread_mutex_lock(&table->state_mutex);
	state = table->state;
	pthread_mutex_unlock(&table->state_mutex);
	return (state);
}

void	set_table_state(t_table *table, enum e_state state)
{
	pthread_mutex_lock(&table->state_mutex);
	table->state = state;
	pthread_mutex_unlock(&table->state_mutex);
}
