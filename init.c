/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:38:49 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/19 11:24:30 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int init_table_mutex(t_table *table)
{
	table->thread_forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo - 1);
	table->thread_dead = malloc(sizeof(pthread_mutex_t));
	table->thread_start_dinner_time= malloc(sizeof(pthread_mutex_t));
	table->thread_last_time_meal= malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->thread_dead, NULL);
	pthread_mutex_init(table->thread_start_dinner_time, NULL);
	pthread_mutex_init(&table->thread_printf, NULL);
	pthread_mutex_init(table->thread_last_time_meal, NULL);
	return (0);
}

int init_philo_mutex(t_philo *philo)
{
	
	philo->thread_left_fork = malloc(sizeof(pthread_mutex_t));
	philo->thread_right_fork = malloc(sizeof(pthread_mutex_t));
	philo->thread_lock_meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->thread_left_fork, NULL);
	pthread_mutex_init(philo->thread_right_fork, NULL);
	pthread_mutex_init(philo->thread_lock_meal, NULL);
	return (0);
}


int init_struct(t_table *table, int argc, char **argv)
{
	int i;
	i = 0;

	table->nbr_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
	if ((table->time_to_die < 6000)
		|| (table->time_to_eat < 6000)
		|| (table->time_to_sleep < 6000))
		{
			return (0); // ERROR
		}
	table->end_simulation = 0;
	table->one_philo_dead = -1;
	init_table_mutex(table);
	table->philos = malloc(sizeof(t_philo) * (table->nbr_philo + 1));
	init_philos(table);
	return (0);	
}

int	init_philos(t_table *table)
{
	int i;
	i = 0;

	while (i < table->nbr_philo)
	{
		table->philos[i].id = i;
		table->philos[i].full = 0;
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		table->philos[i].time_last_meal = -1;
		init_philo_mutex(&table->philos[i]);
		i++;
	}
	i = 0;

	while (i < table->nbr_philo)
	{
		assign_forks(table, i);
		i++;
	}
	return (0);
}

void assign_forks(t_table *table, int i)
{

	if (i == 0)
	{
		table->philos[0].thread_left_fork = &table->thread_forks[0];
		table->philos[0].thread_right_fork = &table->thread_forks[table->nbr_philo];
	}
	else
	{
		table->philos[i].thread_left_fork = &table->thread_forks[i];
		table->philos[i].thread_right_fork = &table->thread_forks[i - 1];
	}
}