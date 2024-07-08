/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:31:53 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/02 12:36:17 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philos_ready(t_mutex *mutex, long *threads, long ph_nbr, t_data *t)
{
	bool	ret;

	ret = false;
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex_lock failed", 2, t);
	if (*threads == ph_nbr)
		ret = true;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex_unlock failed", 2, t);
	return (ret);
}

void	add_long(t_mutex *mutex, long *value, t_data *table)
{
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex_lock failed", 2, table);
	(*value)++;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex_unlock failed", 2, table);
}

void	thinking(t_philo *philo, bool first)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!first)
		write_action(5, philo);
	if (philo->data->nbr_philos % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_sleep(t_think * 0.3, philo->data);
}

void	de_synchrosize_philos(t_philo *philo)
{
	if (philo->data->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_sleep(30000, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
