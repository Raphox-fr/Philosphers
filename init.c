/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:38:49 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/12 12:29:16 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int init_table_mutex(t_table *table)
{
	table->thread_dead = malloc(1 * sizeof(pthread_mutex_t));
	table->thread_start_dinner_time= malloc(1 * sizeof(pthread_mutex_t));

	pthread_mutex_init(table->thread_dead, NULL);
	pthread_mutex_init(table->thread_start_dinner_time, NULL);
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
	table->end_simulation = false;
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
		table->philos[i].full = false;
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		table->philos[i].time_last_meal = 0;
		init_philo_mutex(&table->philos[i]);
		
		// assign_forks(&table->philos[i], i);
		i++;
	}
	return (0);
}