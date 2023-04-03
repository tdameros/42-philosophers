/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:13:36 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:16:18 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_number_of_philosophers_satisfied(t_table *table)
{
	int	number_of_philosophers_satisfied;

	pthread_mutex_lock(&table->number_of_philosophers_satisfied_mutex);
	number_of_philosophers_satisfied = table->number_of_philosophers_satisfied;
	pthread_mutex_unlock(&table->number_of_philosophers_satisfied_mutex);
	return (number_of_philosophers_satisfied);
}

int	set_philosopher_satisfied(t_table *table)
{
	pthread_mutex_lock(&table->number_of_philosophers_satisfied_mutex);
	table->number_of_philosophers_satisfied++;
	pthread_mutex_unlock(&table->number_of_philosophers_satisfied_mutex);
	return (0);
}
