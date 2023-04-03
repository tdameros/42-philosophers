/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:48:35 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/18 16:48:36 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "philosopher.h"
#include "utils.h"

t_philosopher	*initialize_philosopher(size_t position,
									char **argv, t_table *table)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(*philosopher));
	if (philosopher == NULL)
		return (NULL);
	philosopher->id = position;
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	philosopher->table = table;
	philosopher->last_meal = get_time_in_ms();
	if (pthread_mutex_init(&philosopher->last_meal_mutex, NULL) != 0)
		return (free(philosopher), NULL);
	philosopher->count_meal = 0;
	if (argv[5] != NULL)
		philosopher->max_meal = ft_atoi(argv[5]);
	else
		philosopher->max_meal = -1;
	philosopher->take_forks = false;
	return (philosopher);
}

int	get_index_right_fork(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		return (philosopher->id - 1);
	else
	{
		if (philosopher->id - 1 == 0)
			return (philosopher->table->number_of_philosophers - 1);
		else
			return (philosopher->id - 2);
	}
}

int	get_index_left_fork(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		if (philosopher->id - 1 == 0)
			return (philosopher->table->number_of_philosophers - 1);
		else
			return (philosopher->id - 2);
	}
	else
		return (philosopher->id - 1);
}

size_t	get_last_meal(t_philosopher *philosopher)
{
	size_t	last_meal;

	pthread_mutex_lock(&philosopher->last_meal_mutex);
	last_meal = philosopher->last_meal;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (last_meal);
}

int	set_last_meal(t_philosopher *philosopher, size_t time_in_ms)
{
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal = time_in_ms;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (1);
}
