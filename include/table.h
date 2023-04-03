/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:46:31 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/18 16:46:33 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum e_state {
	FINISH = 0,
	RUNNING = 1,
	WAITING = 2
}	t_state;

typedef struct s_table
{
	pthread_t		*threads;
	pthread_mutex_t	*forks_mutex;
	size_t			start_time_in_ms;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	logs_mutex;
	pthread_mutex_t	number_of_philosophers_satisfied_mutex;
	int				number_of_philosophers;
	int				number_of_philosophers_satisfied;
	t_state			state;

}	t_table;

//	eat.c
int				set_philosopher_satisfied(t_table *table);
int				get_number_of_philosophers_satisfied(t_table *table);

//	table.c
t_state			get_table_state(t_table *table);
void			set_table_state(t_table *table, enum e_state state);
void			free_table(t_table *table);
t_table			*initialize_table(size_t number_of_philosophers);

#endif
