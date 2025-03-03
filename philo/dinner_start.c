/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/03 17:00:46 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	go_eat(t_philo *philo)
{
	pick_up_the_forks(philo);
	pthread_mutex_lock(philo->table->thrd_gbl);
	
	if (philo->table->end_simulation == 1 && philo->table->nbr_limit_meals == -1)
	{
		pthread_mutex_unlock(philo->table->thrd_gbl);
		release_the_forks(philo);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	pthread_mutex_lock(philo->table->thrd_gbl);
	philo->time_last_meal = set_timer();
	philo->meal_counter = philo->meal_counter + 1;
	if (philo->full != 1)
	{
		my_printf(philo, "has taken a fork", 0);
		my_printf(philo, "has taken a fork", 0);
		my_printf(philo, "is eating", 0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	pthread_mutex_lock(philo->table->thrd_gbl);
	
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thrd_gbl);
		release_the_forks(philo);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	ft_usleep(philo->table->time_to_eat, philo->table);
	release_the_forks(philo);
	return (1);
}

int	go_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->table->thrd_gbl);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thrd_gbl);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	my_printf(philo, "is sleeping", 0);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	pthread_mutex_lock(philo->table->thrd_gbl);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thrd_gbl);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	return (1);
}

int	go_think(t_philo *philo)
{
	pthread_mutex_lock(philo->table->thrd_gbl);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thrd_gbl);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thrd_gbl);
	my_printf(philo, "is thinking", 0);
	return (1);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	if (philo->table->nbr_philo == 1)
		return (0);
	while (is_philo_dead(philo) == 1)
	{
		if (go_eat(philo) == 0)
			return (0);
		if (go_sleep(philo) == 0)
			return (0);
		if (go_think(philo) == 0)
			return (0);
	}
	return (NULL);
}

int	dinner_start(t_table *table)
{
	int			i;
	pthread_t	watch;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return (0);
	if (table->nbr_philo == 1)
		return (one_philo_table(table), 0);
	table->start_dinner_time = set_timer();
	if (pthread_create(&watch, NULL, &watch_simulation, table) != 0)
	{
		return (destroy_all(table, i), -1);
		return (-1);
	}
	
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
			&table->philos[i]) != 0)
			{
				printf("TA GUEIE");
				return (destroy_all(table, i), -1);
			}
			i++;
	}
	pthread_join(watch, NULL);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			printf("COUCOU");
			return (destroy_all(table, i), -1);
		}
		i++;
	}
	return (destroy_all(table, i), 1);
}

void destroy_all(t_table *table, int i)
{
	int j;
	j = 0;
	
	while (j < table->nbr_philo - 1)
	{
		free(table->philos[j].thread_l_fork);
		free(table->philos[j].thread_r_fork);
		j++;
	}
	// pthread_mutex_destroy(table->thrd_gbl);
	// free(table->philos);
	// pthread_mutex_destroy(&table->thread_printf);
	// pthread_mutex_destroy(table->thread_forks);
	// free(table->thrd_gbl);
	// free(table->thread_forks);
}
