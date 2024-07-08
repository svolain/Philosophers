/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:14:31 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/06 13:40:06 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(int flag, t_philo *philo)
{
	long	time;

	if (philo->full)
		return ;
	if (pthread_mutex_lock(&philo->data->write_mtx) != 0)
		error_exit("Error: Mutex lock failed", 2, philo->data);
	time = get_time(2, philo->data) - philo->data->start_eating;
	if ((flag == 1 || flag == 2) && !simulation_finish(philo->data))
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if ((flag == 3) && !simulation_finish(philo->data))
		printf("%ld %d is eating\n", time, philo->id);
	else if ((flag == 4) && !simulation_finish(philo->data))
		printf("%ld %d is sleeping\n", time, philo->id);
	else if ((flag == 5) && !simulation_finish(philo->data))
		printf("%ld %d is thinking\n", time, philo->id);
	else if ((flag == 6) && !simulation_finish(philo->data))
		printf("%ld %d died\n", time, philo->id);
	if (pthread_mutex_unlock(&philo->data->write_mtx) != 0)
		error_exit("Error: Mutex unlock failed", 2, philo->data);
}

long	get_time(int flag, t_data *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		error_exit("Error: gettimeofday failed", 2, table);
	if (flag == 1)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	if (flag == 2)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (flag == 3)
		return ((tv.tv_sec * 1000000) + (tv.tv_usec));
	else
		error_exit("Error: wrong input to get_time", 2, table);
	return (0);
}

void	ft_sleep(long time, t_data *table)
{
	long	start;
	long	time_spent;
	long	time_remaining;

	start = get_time(3, table);
	while ((get_time(3, table) - start) < time)
	{
		if (simulation_finish(table))
			break ;
		time_spent = get_time(3, table) - start;
		time_remaining = time - time_spent;
		if (time_remaining > 1000)
			usleep(time_remaining / 2);
		else
		{
			while (get_time(3, table) - start < time)
				continue ;
		}
	}
}

void	eat(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->right_fork->fork) != 0)
		error_exit("Error: Mutex_lock failed", 2, ph->data);
	write_action(1, ph);
	if (pthread_mutex_lock(&ph->left_fork->fork) != 0)
		error_exit("Error: Mutex_lock failed", 2, ph->data);
	write_action(2, ph);
	set_long(&ph->ph_mtx, &ph->last_meal, get_time(2, ph->data), ph->data);
	ph->nbr_meals++;
	write_action(3, ph);
	ft_sleep(ph->data->time_to_eat, ph->data);
	if (ph->data->nbr_meals > 0 && ph->nbr_meals == ph->data->nbr_meals)
		set_bool(&ph->ph_mtx, &ph->full, true, ph->data);
	if (pthread_mutex_unlock(&ph->right_fork->fork) != 0)
		error_exit("Error: Mutex_unlock failed", 2, ph->data);
	if (pthread_mutex_unlock(&ph->left_fork->fork) != 0)
		error_exit("Error: Mutex_unlock failed", 2, ph->data);
}
