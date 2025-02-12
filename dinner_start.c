/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/12 13:13:10 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <unistd.h>

int is_philo_dead(t_philo *philo)
{
	// if time le sleep + time to eat < time globale tu dead
	// pthread_mutex_lock(philo->table->thread_dead);
	// philo->table->one_philo_dead = 1;
	// pthread_mutex_lock(philo->table->thread_dead);
	return (1);
		
}

int go_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);
	philo->time_last_meal = set_timer();
	philo->meal_counter = philo->meal_counter + 1;
	if ((philo->table->nbr_limit_meals != -1) && (philo->meal_counter > philo->table->nbr_limit_meals))
			return(write(2, "MAX MEAL DEPASSER", 17), 0);
	my_printf(philo, "is eating");
	usleep(1000000);
	pthread_mutex_unlock(philo->thread_lock_meal);
	return (1);
}

int go_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);
	// if (set_timer() - philo->time_last_meal > philo->table->time_to_die)
	// 		return(write(2, "TOO MUCH TIME", 13), 0);			
	my_printf(philo, "is sleeping");
	usleep(1000000);
	pthread_mutex_unlock(philo->thread_lock_meal);
	return (1);
}

int go_think(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);
	// if (set_timer() - philo->time_last_meal > philo->table->time_to_die)
	// 		return(write(2, "TOO MUCH TIME", 13), 0);
	my_printf(philo, "is thinking");
	usleep(1000000);
	pthread_mutex_unlock(philo->thread_lock_meal);
	return (1);
}




void *dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	int i;
	i = 0;
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

void dinner_start(t_table *table)
{
	int i;
	i = 0;
	
	if (table->nbr_limit_meals == 0)
		return ;
	if (table->nbr_philo == 1)
		return ;
	else
	{
		while (i < table->nbr_philo)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
		i = 0;
		while (i < table->nbr_philo)
		{
			pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}

	}
}