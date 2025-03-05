/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/05 12:45:03 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	go_eat(t_philo *philo)
{
	pick_up_the_forks(philo);
	pthread_mutex_lock(philo->table->thrd_gbl);
	if (philo->table->end_simulation == 1)
		return (pthread_mutex_unlock(philo->table->thrd_gbl),
			release_the_forks(philo), 0);
	pthread_mutex_unlock(philo->table->thrd_gbl);
	pthread_mutex_lock(philo->table->thrd_gbl);
	philo->time_last_meal = set_timer();
	philo->meal_counter = philo->meal_counter + 1;
	if (philo->table->nbr_limit_meals != -2
		&& philo->meal_counter > philo->table->nbr_limit_meals)
		return (pthread_mutex_unlock(philo->table->thrd_gbl),
			release_the_forks(philo), 1);
	my_printf(philo, "has taken a fork", 0);
	my_printf(philo, "has taken a fork", 0);
	my_printf(philo, "is eating", 0);
	pthread_mutex_unlock(philo->table->thrd_gbl);
	pthread_mutex_lock(philo->table->thrd_gbl);
	if (philo->table->end_simulation == 1)
		return (pthread_mutex_unlock(philo->table->thrd_gbl),
			release_the_forks(philo), 0);
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

	philo = (t_philo *)data;
	if (philo->table->nbr_philo == 1)
		return (0);
	while (is_philo_dead() == 1)
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
		return (destroy_all(table), -1);
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
				&table->philos[i]) != 0)
			return (destroy_all(table), -1);
		i++;
	}
	if (pthread_join(watch, NULL) != 0)
		return (destroy_all(table), -1);
	i = 0;
	if (dinner_start_2(table) == -1)
		return (-1);
	return (destroy_all(table), 1);
}

// int	go_eat(t_philo *philo)
// {
// 	pick_up_the_forks(philo);
// 	pthread_mutex_lock(philo->table->thrd_gbl);

// 	if (philo->table->end_simulation == 1)
// 	{
// 		pthread_mutex_unlock(philo->table->thrd_gbl);
// 		release_the_forks(philo);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(philo->table->thrd_gbl);
// 	pthread_mutex_lock(philo->table->thrd_gbl);
// 	philo->time_last_meal = set_timer();
// 	philo->meal_counter = philo->meal_counter + 1;
// 	if (philo->table->nbr_limit_meals != -2
// && philo->meal_counter >= philo->table->nbr_limit_meals + 1)
// 	{
// 		pthread_mutex_unlock(philo->table->thrd_gbl);
// 		release_the_forks(philo);
// 		return (1);
// 	}
// 	my_printf(philo, "has taken a fork", 0);
// 	my_printf(philo, "has taken a fork", 0);
// 	my_printf(philo, "is eating", 0);
// 	pthread_mutex_unlock(philo->table->thrd_gbl);
// 	pthread_mutex_lock(philo->table->thrd_gbl);

// 	if (philo->table->end_simulation == 1)
// 	{
// 		pthread_mutex_unlock(philo->table->thrd_gbl);
// 		release_the_forks(philo);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(philo->table->thrd_gbl);
// 	ft_usleep(philo->table->time_to_eat, philo->table);
// 	release_the_forks(philo);
// 	return (1);
// }