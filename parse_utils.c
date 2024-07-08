/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:45 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/02 12:35:39 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == ' ' || str[i] == '\f' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			error_exit("Error: Negative input", 1, NULL);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != 0)
		error_exit("Error: Non numeric input", 1, NULL);
	if (n > INT_MAX)
		error_exit("Error: Input bigger than INT_MAX", 1, NULL);
	return (n);
}

void	parse_input(t_data *table, char **argv)
{
	table->nbr_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("Error: timestamp needs to be more than 60ms", 1, NULL);
	if (argv[5])
		table->nbr_meals = ft_atol(argv[5]);
	else
		table->nbr_meals = -1;
}

static void	get_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->data->nbr_philos;
	philo->right_fork = &forks[(i + 1) % philo_nbr];
	philo->left_fork = &forks[i];
	if ((philo->id % 2) == 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork = &forks[(i + 1) % philo_nbr];
	}
}

static void	init_philo(t_data *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nbr_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nbr_meals = 0;
		philo->data = table;
		if (pthread_mutex_init(&philo->ph_mtx, NULL) != 0)
			error_exit("Error: Mutex_init failed", 2, table);
		get_forks(philo, table->forks, i);
	}
}

void	table_init(t_data *table)
{
	int	i;

	i = -1;
	table->end = false;
	table->start = false;
	table->threads_run_nbr = 0;
	table->philos = malloc(table->nbr_philos * sizeof(t_philo));
	if (table->philos == NULL)
		error_exit("Error: Failed to allocate memory", 1, NULL);
	table->forks = malloc(table->nbr_philos * sizeof(t_fork));
	if (table->forks == NULL)
		error_exit("Error: Failed to allocate memory", 1, table);
	if (pthread_mutex_init(&table->write_mtx, NULL) != 0)
		error_exit("Error: Failed mutex init", 1, table);
	if (pthread_mutex_init(&table->data_mtx, NULL) != 0)
		error_exit("Error: Failed mutex init", 2, table);
	while (++i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			error_exit("Error: Failed mutex init", 2, table);
		table->forks[i].id = i;
	}
	init_philo(table);
}
