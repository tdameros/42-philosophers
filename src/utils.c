/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:20:44 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/31 00:20:45 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <errno.h>

#include "utils.h"

static size_t	count_white_spaces(const char *s);
static int		check_overflow(const char *str, size_t index,
					long result, int sign);

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	result;
	int		overflow;
	int		sign;
	size_t	index;

	result = 0;
	sign = 1;
	str += count_white_spaces(str);
	index = 0;
	if (str[index] == '-')
	{
		sign = -1;
		str++;
	}
	else if (str[index] == '+')
		str++;
	while (ft_isdigit(str[index]))
	{
		overflow = check_overflow(str, index, result, sign);
		if (overflow)
			return (overflow);
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return ((int) result * sign);
}

static size_t	count_white_spaces(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index] == ' ' || s[index] == '\f' || s[index] == '\n'
		|| s[index] == '\r' || s[index] == '\t' || s[index] == '\v')
		index++;
	return (index);
}

static int	check_overflow(const char *str, size_t index, long result, int sign)
{
	if (INT_MAX / 10 < result * sign
		|| INT_MAX - (str[index] - '0') < result * 10 * sign)
	{
		errno = EOVERFLOW;
		return ((int) INT_MAX);
	}
	if (INT_MIN / 10 > result * sign
		|| INT_MIN + (str[index] - '0') > result * 10 * sign)
	{
		errno = EOVERFLOW;
		return ((int) INT_MIN);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*(unsigned char *)s1 + *(unsigned char *)s2 != 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
