/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:59:28 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:59:30 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

void	*philosopher_routine(void *philosopher_ptr);
void	*single_philosopher_routine(void *philosopher_ptr);
void	*run_monitoring(void *philosophers_ptr);

#endif
