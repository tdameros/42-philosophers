/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:59:36 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:59:37 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

# include <stdlib.h>

# include "philosopher.h"

# define MSG_FORK "\001\e[0;36m\002has taken a fork\001\e[m\002"
# define MSG_EAT "\001\e[0;35m\002is eating\001\e[m\002"
# define MSG_SLEEP "\001\e[0;33m\002is sleeping\001\e[m\002"
# define MSG_THINK "\001\e[0;37m\002is thinking\001\e[m\002"
# define MSG_DIE "\001\e[0;31m\002died\001\e[m\002"

int		print_log(t_philosopher *philosopher, char *message);
int		print_error(void);

#endif
