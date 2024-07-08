/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:30:57 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/06 11:58:45 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = table->philos + i;
		if (pthread_mutex_destroy(&philo->ph_mtx) != 0)
			error_exit("Error: Mutex_destroy failed", 4, table);
	}
	if (pthread_mutex_destroy(&table->data_mtx) != 0)
		error_exit("Error: Mutex_destroy failed", 4, table);
	if (pthread_mutex_destroy(&table->write_mtx) != 0)
		error_exit("Error: Mutex_destroy failed", 4, table);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *msg, int flag, t_data *table)
{
	if (flag == 2)
		free_data(table);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
