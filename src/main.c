/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:47:31 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/18 16:47:31 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "table.h"
#include "philosopher.h"
#include "logs.h"
#include "utils.h"

static int	parse_arguments(int argc, char **argv);
static bool	is_number(char *string);
static int	raise_error(void);
static int	run_simulation(t_table *table, t_philosopher **philosophers);

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philosopher	**philosophers;
	int				exit_code;

	if (parse_arguments(argc, argv) == 1)
		return (raise_error());
	table = initialize_table(atoi(argv[1]));
	if (table == NULL)
		return (raise_error());
	philosophers = initialize_philosophers(table, argv);
	if (philosophers == NULL)
		return (free_table(table), raise_error());
	if (run_simulation(table, philosophers) < 0)
	{
		exit_code = 1;
		raise_error();
	}
	else
		exit_code = 0;
	free_table(table);
	free_philosophers(philosophers);
	return (exit_code);
}

static int	parse_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (!is_number(argv[1]) || !is_number(argv[2])
		|| !is_number(argv[3]) || !is_number(argv[4]))
		return (1);
	if (argv[5] != NULL && !is_number(argv[5]))
		return (1);
	ft_atoi(argv[1]);
	ft_atoi(argv[2]);
	ft_atoi(argv[3]);
	ft_atoi(argv[4]);
	if (argv[5] != NULL)
		ft_atoi(argv[5]);
	return (errno != 0);
}

static bool	is_number(char *string)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
	{
		if (!ft_isdigit(string[index]))
			return (false);
		index++;
	}
	return (true);
}

static int	raise_error(void)
{
	print_error();
	return (1);
}

static int	run_simulation(t_table *table, t_philosopher **philosophers)
{
	if (table->number_of_philosophers > 0 && philosophers[0]->max_meal == 0)
		return (0);
	if (table->number_of_philosophers == 1
		&& run_philosopher(philosophers, table) < 0)
		return (-1);
	if (table->number_of_philosophers > 1
		&& run_philosophers(philosophers, table) < 0)
		return (-1);
	return (0);
}
