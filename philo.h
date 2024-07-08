/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:54:16 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/06 10:02:44 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mutex	fork;
	int		id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		nbr_meals;
	bool		full;
	long		last_meal;
	t_fork		*right_fork;
	t_fork		*left_fork;
	pthread_t	th_id;
	t_mutex		ph_mtx;
	t_data		*data;
}	t_philo;

struct s_data
{
	long		nbr_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_meals;
	long		start_eating;
	long		threads_run_nbr;
	bool		end;
	bool		start;
	pthread_t	monitor;
	t_mutex		data_mtx;
	t_mutex		write_mtx;
	t_fork		*forks;
	t_philo		*philos;
};

void	error_exit(const char *msg, int flag, t_data *table);
void	parse_input(t_data *table, char **argv);
void	table_init(t_data *table);
void	start_simulation(t_data *table, int i);
void	set_bool(t_mutex *mutex, bool *dest, bool value, t_data *table);
bool	get_bool(t_mutex *mutex, bool *value, t_data *table);
void	set_long(t_mutex *mutex, long *dest, long value, t_data *table);
long	get_long(t_mutex *mutex, long *value, t_data *table);
bool	simulation_finish(t_data *table);
void	ft_sleep(long time, t_data *table);
void	write_action(int flag, t_philo *philo);
void	eat(t_philo *ph);
bool	philos_ready(t_mutex *mutex, long *threads, long ph_nbr, t_data *t);
void	add_long(t_mutex *mutex, long *value, t_data *table);
long	get_time(int flag, t_data *table);
void	free_data(t_data *table);
void	de_synchrosize_philos(t_philo *philo);
void	thinking(t_philo *philo, bool first);

#endif