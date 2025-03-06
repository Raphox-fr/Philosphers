/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:38:49 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/06 12:59:59 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table_mutex(t_table *table)
{
	table->thrd_gbl = malloc(sizeof(pthread_mutex_t));
	if (table->thrd_gbl == NULL)
		return (-1);
	if (pthread_mutex_init(table->thrd_gbl, NULL) != 0)
		return (free(table->thrd_gbl), -1);
	if (pthread_mutex_init(&table->thread_printf, NULL) != 0)
	{
		pthread_mutex_destroy(table->thrd_gbl);
		free(table->thrd_gbl);
		return (-1);
	}
	table->thread_forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo);
	if (table->thread_forks == NULL)
	{
		pthread_mutex_destroy(table->thrd_gbl);
		pthread_mutex_destroy(&table->thread_printf);
		return (free(table->thrd_gbl), -1);
	}
	if (init_forks(table) == -1)
	{
		pthread_mutex_destroy(table->thrd_gbl);
		pthread_mutex_destroy(&table->thread_printf);
		return (free(table->thrd_gbl), free(table->thread_forks), -1);
	}
	return (0);
}

int	init_struct(t_table *table, int argc, char **argv)
{
	if (argc == 0)
		return (0);
	table->nbr_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
	{
		table->nbr_limit_meals = ft_atol(argv[5]);
		if (table->nbr_limit_meals <= 0)
			return (printf("Number of meals too low\n"), -1);
	}
	else
		table->nbr_limit_meals = -2;
	if ((table->time_to_die < 60) || (table->time_to_eat < 60)
		|| (table->time_to_sleep < 60))
		return (printf("Unaccepted values\n"), -1);
	table->end_simulation = 0;
	table->one_philo_dead = -1;
	if (init_table_mutex(table) == -1)
		return (-1);
	table->philos = malloc(sizeof(t_philo) * (table->nbr_philo));
	init_philos(table);
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		table->philos[i].id = i;
		table->philos[i].full = 0;
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		table->philos[i].time_last_meal = -1;
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

void	assign_forks(t_table *table, int i)
{
	if (i == 0 && table->nbr_philo == 1)
	{
		table->philos[0].thread_l_fork = &table->thread_forks[0];
	}
	if (i == 0)
	{
		table->philos[0].thread_l_fork = &table->thread_forks[0];
		table->philos[0].thread_r_fork = &table->thread_forks[table->nbr_philo
			- 1];
	}
	else
	{
		table->philos[i].thread_l_fork = &table->thread_forks[i];
		table->philos[i].thread_r_fork = &table->thread_forks[i - 1];
	}
}
