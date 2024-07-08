/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:40:18 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/06 08:29:07 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		table_init(&table);
		if (argc == 6 && table.nbr_meals == 0)
			free_data(&table);
		else
		{
			start_simulation(&table, -1);
			free_data(&table);
		}
	}
	else
		error_exit("Wrong input: Correct: ./philo 5 800 200 200 [5]", 1, NULL);
	return (0);
}
