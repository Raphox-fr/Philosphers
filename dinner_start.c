/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 17:44:49 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int is_philo_dead(t_philo *philo)
{
	// if time le sleep + time to eat < time globale tu dead
	// pthread_mutex_lock(philo->table->thread_dead);
	// philo->table->one_philo_dead = 1;
	// pthread_mutex_lock(philo->table->thread_dead);
	return (0);
		
}

int go_eat(t_philo *philo)
{
	// pthread_mutex_lock(philo->thread_lock_meal);
	// printf("%d", philo->id);
	// philo->time_last_meal = set_timer() - philo->time_last_meal;
	// philo->meal_counter = philo->meal_counter + 1;
	// if (philo->meal_counter > philo->table->nbr_limit_meals)
	// 	return (0);
	write(1, "EATING\n", 7);
	// my_printf(philo, "is eating");
	
	// pthread_mutex_unlock(philo->thread_lock_meal);
	
	return (1);
}




void *dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	write(1, "BIEN JOUER\n", 11);
	// pthread_mutex_lock(philo->table->thread_start_dinner_time);
	// philo->table->start_dinner_time = set_timer();
	// pthread_mutex_unlock(philo->table->thread_start_dinner_time);


	int i;
	i = 0;
	while (i < 9)
	{
		if (go_eat(philo) == 0)
			return (0);
		i++;
		// if (go_sleep()) == 0)
		// 	return (0);
		// if (go_think() == 0)
		// 	return (0);
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
	}	
}