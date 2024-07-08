/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:59:50 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/02 12:39:22 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!get_bool(&p->data->data_mtx, &p->data->start, p->data))
		continue ;
	set_long(&p->ph_mtx, &p->last_meal, get_time(2, p->data), p->data);
	add_long(&p->data->data_mtx, &p->data->threads_run_nbr, p->data);
	write_action(1, p);
	while (!simulation_finish(p->data))
		usleep(200);
	return (NULL);
}

bool	dead_philo(t_philo *p)
{
	long	ts;
	long	ttd;

	if (get_bool(&p->ph_mtx, &p->full, p->data))
		return (false);
	ts = get_time(2, p->data) - get_long(&p->ph_mtx, &p->last_meal, p->data);
	ttd = p->data->time_to_die / 1000;
	if (ts > ttd)
		return (true);
	return (false);
}

void	*monitor_death(void	*data)
{
	t_data	*t;
	int		i;

	t = (t_data *)data;
	while (!philos_ready(&t->data_mtx, &t->threads_run_nbr, t->nbr_philos, t))
		continue ;
	while (!simulation_finish(t))
	{
		i = -1;
		while (++i < t->nbr_philos && !simulation_finish(t))
		{
			if (dead_philo(t->philos + i))
			{
				write_action(6, t->philos + i);
				set_bool(&t->data_mtx, &t->end, true, t);
			}
		}
	}
	return (NULL);
}

void	*dinner(void *data)
{
	t_philo	*philo;
	t_data	*table;

	philo = (t_philo *)data;
	table = philo->data;
	while (!get_bool(&table->data_mtx, &table->start, table))
		continue ;
	set_long(&philo->ph_mtx, &philo->last_meal, get_time(2, table), table);
	add_long(&table->data_mtx, &table->threads_run_nbr, table);
	de_synchrosize_philos(philo);
	while (!simulation_finish(table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_action(4, philo);
		ft_sleep(table->time_to_sleep, table);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_simulation(t_data *t, int i)
{
	if (t->nbr_philos == 1)
	{
		if (pthread_create(&t->philos[0].th_id, NULL, one_philo,
				&t->philos[0]) != 0)
			error_exit("Error: Pthread_create failed", 2, t);
	}
	else
	{
		while (++i < t->nbr_philos)
			if (pthread_create(&t->philos[i].th_id, NULL, dinner,
					&t->philos[i]) != 0)
				error_exit("Erro: failed thread init", 2, t);
	}
	if (pthread_create(&t->monitor, NULL, monitor_death, t) != 0)
		error_exit("Error: Pthread_create failed", 2, t);
	t->start_eating = get_time(2, t);
	set_bool(&t->data_mtx, &t->start, true, t);
	i = -1;
	while (++i < t->nbr_philos)
		if (pthread_join(t->philos[i].th_id, NULL) != 0)
			error_exit("Error: Pthread_join failed", 2, t);
	set_bool(&t->data_mtx, &t->end, true, t);
	if (pthread_join(t->monitor, NULL) != 0)
		error_exit("Error: Pthread_join failed", 2, t);
}
