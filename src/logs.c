/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:19:10 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:19:11 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "logs.h"
#include "philosopher.h"
#include "utils.h"

int	print_log(t_philosopher *philosopher, char *message)
{
	size_t	timestamp;

	pthread_mutex_lock(&philosopher->table->logs_mutex);
	timestamp = get_time_in_ms() - philosopher->table->start_time_in_ms;
	if (get_table_state(philosopher->table) == RUNNING
		|| ft_strcmp(message, MSG_DIE) == 0)
		printf("%ld %d %s\n", timestamp, philosopher->id, message);
	pthread_mutex_unlock(&philosopher->table->logs_mutex);
	return (1);
}

int	print_error(void)
{
	return (write(STDERR_FILENO, "Error\n", 6));
}
