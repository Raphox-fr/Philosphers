/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 12:01:28 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int is_philo_dead(t_philo *philo)
{
	// if time le sleep + time to eat < time globale tu dead
	pthread_mutex_lock(philo->table->thread_dead);
	philo->table->one_philo_dead = 1;
	pthread_mutex_lock(philo->table->thread_dead);
	return (0);
		
}

int go_eat(t_philo *philo)
{
	philo->meal_counter = philo->meal_counter + 1; 
	if (philo->meal_counter > philo->table->nbr_limit_meals)
	{
		return (0);
	}
	printf()
	
	
	
	
	
	
	
	
	return (0);
}




void* dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	pthread_mutex_lock(philo->table->thread_start_dinner_time);
	philo->table->start_dinner_time = set_timer();
	pthread_mutex_unlock(philo->table->thread_start_dinner_time);

	while (is_philo_dead(philo) == 0)
	{
		if (go_eat(philo) == 0)
			return (0);
		if (go_sleep()) == 0)
			return (0);
		if (go_think() == 0)
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
			printf("valeur i %d\n", i);
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}	
}