/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:06:55 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/02 12:38:17 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value, t_data *table)
{
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex lock failed", 2, table);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex unlock failed", 2, table);
}

bool	get_bool(t_mutex *mutex, bool *value, t_data *table)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex lock failed", 2, table);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex unlock failed", 2, table);
	return (ret);
}

void	set_long(t_mutex *mutex, long *dest, long value, t_data *table)
{
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex lock failed", 2, table);
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex unlock failed", 2, table);
}

long	get_long(t_mutex *mutex, long *value, t_data *table)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Error: Mutex lock failed", 2, table);
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Error: Mutex unlock failed", 2, table);
	return (ret);
}

bool	simulation_finish(t_data *table)
{
	bool	ret;

	ret = get_bool(&table->data_mtx, &table->end, table);
	return (ret);
}
