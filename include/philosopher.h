/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:46:26 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/27 22:38:00 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>

# include "table.h"

typedef struct s_philosopher
{
	t_table			*table;
	size_t			last_meal;
	pthread_mutex_t	last_meal_mutex;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_meal;
	int				max_meal;
	bool			take_forks;
}	t_philosopher;

//	philosopher.c
t_philosopher	*initialize_philosopher(size_t position,
					char **argv, t_table *table);
int				get_index_right_fork(t_philosopher *philosopher);
int				get_index_left_fork(t_philosopher *philosopher);
size_t			get_last_meal(t_philosopher *philosopher);
int				set_last_meal(t_philosopher *philosopher, size_t time_in_ms);

//	philosophers.c
t_philosopher	**initialize_philosophers(t_table *table, char **argv);
void			free_philosophers(t_philosopher **philosophers);
int				run_philosophers(t_philosopher **philosophers, t_table *table);
int				run_philosopher(t_philosopher **philosophers, t_table *table);

//	forks.c
int				take_forks(t_philosopher *philosopher);
int				put_forks(t_philosopher *philosopher);

#endif
