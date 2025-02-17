/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/17 19:03:23 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <unistd.h>

// int ft_usleep(long time)
// {
// 	long start;
// 	start = set_timer();
// 	while ((set_timer() - start) < time)
// 	{
// 		usleep(500);
// 	}
// 	return (1);
// }


int pick_up_the_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) // est pair
	{
		pthread_mutex_lock(philo->thread_left_fork);
		my_printf(philo, "has taken a right fork", 0);		
		pthread_mutex_lock(philo->thread_right_fork);
		my_printf(philo, "has taken a left fork", 0);		
	}
	else
	{
		pthread_mutex_lock(philo->thread_left_fork);
		pthread_mutex_lock(philo->thread_right_fork);		
	}
	return (1);
}

int release_the_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) // est pair
	{
		pthread_mutex_unlock(philo->thread_left_fork);
		pthread_mutex_unlock(philo->thread_right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->thread_right_fork);
		pthread_mutex_unlock(philo->thread_left_fork);
	}
	
	return (1);
}


int is_philo_dead(t_philo *philo)
{
	return (1);
}

int go_eat(t_philo *philo)
{
	//pthread_mutex_lock(philo->thread_lock_meal);
	pick_up_the_forks(philo);
	// philo->time_last_meal = set_timer();
	// philo->meal_counter = philo->meal_counter + 1;
	my_printf(philo, "is eating", 0);
	usleep(philo->table->time_to_eat);
	// pthread_mutex_lock(philo->table->thread_dead);
	// if (philo->table->end_simulation == 1)
	// {
	// 	write(1, "END SIMULATION\n", 15);
	// 	pthread_mutex_unlock(philo->table->thread_dead);
	// 	pthread_mutex_unlock(philo->table->thread_last_time_meal);
	// 	pthread_mutex_unlock(philo->thread_lock_meal);
	// 	return (0);
	// }
	// pthread_mutex_unlock(philo->table->thread_dead);
	//pthread_mutex_unlock(philo->thread_lock_meal);
	release_the_forks(philo);
	return (1);
}

int go_sleep(t_philo *philo)
{
	// pthread_mutex_lock(philo->thread_lock_meal);
	my_printf(philo, "is sleeping", 0);
	usleep(philo->table->time_to_sleep);
	// pthread_mutex_lock(philo->table->thread_dead);
	// if (philo->table->end_simulation == 1)
	// {
	// 	pthread_mutex_unlock(philo->table->thread_dead);
	// 	pthread_mutex_unlock(philo->thread_lock_meal);
	// 	return (0);
	// }
	// pthread_mutex_unlock(philo->table->thread_dead);		
	// pthread_mutex_unlock(philo->thread_lock_meal);
	return (1);
}

int go_think(t_philo *philo)
{
	// pthread_mutex_lock(philo->thread_lock_meal);
	my_printf(philo, "is thinking", 0);
	// pthread_mutex_lock(philo->table->thread_dead);
	// if (philo->table->end_simulation == 1)
	// {
	// 	pthread_mutex_unlock(philo->table->thread_dead);
	// 	pthread_mutex_unlock(philo->thread_lock_meal);
	// 	return (0);
	// }
	// pthread_mutex_unlock(philo->table->thread_dead);
	// pthread_mutex_unlock(philo->thread_lock_meal);

	return (1);
}


void *dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	int i;
	i = 0;
	// if (philo->id % 2 == 0)
	// 	usleep(philo->table->time_to_eat);
	while (is_philo_dead(philo) == 1)
	{
		if (go_eat(philo) == 0)
			return (0);
		if (go_sleep(philo) == 0)
			return (0);
		if (go_think(philo) == 0)
			return (0);
	}
	printf("SORTIE DE LA BOUCLE");
	return (NULL);
}


void dinner_start(t_table *table)
{
	int i;
	i = 0;

	pthread_t watch;
	
	if (table->nbr_limit_meals == 0)
		return ;
	if (table->nbr_philo == 1)
		return ;
	else
	{
		table->start_dinner_time = set_timer();
	// if (pthread_create(&watch, NULL, &watch_simulation, table) == 0)
	// 	pthread_detach(watch);
		
		while (i < table->nbr_philo)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
		// if (pthread_join(watch, NULL) == 0)
		// 		pthread_detach(watch);		
		i = 0;
		while (i < table->nbr_philo)
		{
			pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}
	}
	// pthread_mutex_destroy(&table->thread_printf);
}

// void *watch_simulation(void *data)
// {
// 	t_table *table;
// 	table = (t_table *)data;

// 	long i;
// 	i = 0;

// 	long pin;
// 	pin = 0;

// 	while (table->end_simulation != 1)
// 	{
// 		i = 0; 
// 		while (i < table->nbr_philo)
// 		{
// 			pthread_mutex_lock(table->thread_dead);
// 			if (table->philos[i].meal_counter == table->nbr_limit_meals && table->nbr_limit_meals != -1)
// 			{
// 				pin++;
// 				if (pin == table->nbr_philo - 1)
// 				{
// 					table->end_simulation = 1;
// 					my_printf(&table->philos[i], "END SIMULATION", 1);
// 					pthread_mutex_unlock(table->thread_dead);
// 					exit(0);
// 				}
// 			}
// 			if (table->philos[i].time_last_meal != -1 && ((set_timer() - table->philos[i].time_last_meal) * 1000) > table->time_to_die)
// 			{
// 				table->end_simulation = 1;
// 				my_printf(&table->philos[i], "too much time", 1);
// 				pthread_mutex_unlock(table->thread_dead);
// 				exit(0);
// 			}
// 			pthread_mutex_unlock(table->thread_dead);

// 			usleep(100);
// 			i++;
// 		}
// 		pin = 0;
// 	}
// 	return (NULL);
// }


// {
// 		if (((set_timer() - philo->time_last_meal) * 1000) > philo->table->time_to_die)
// 			return(write(2, "TOO MUCH TIME\n", 14), 0);		
// 	}

// void dinner_start(t_table *table)
// {
// 	int i;
// 	i = 0;

// 	pthread_t watch;
	
// 	if (table->nbr_limit_meals == 0)
// 		return ;
// 	if (table->nbr_philo == 1)
// 		return ;
// 	else
// 	{
// 		table->start_dinner_time = set_timer();
// 	if (pthread_create(&watch, NULL, &watch_simulation, table) == 0)
// 		pthread_detach(watch);
		
// 		while (i < table->nbr_philo)
// 		{
// 			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
// 			i++;
// 		}
// 		i = 0;
		
// 		if (pthread_join(watch, NULL) == 0)
// 				pthread_detach(watch);

// 		while (i < table->nbr_philo)
// 		{
// 			if (pthread_join(table->philos[i].thread_id, NULL) == 0)
// 			{
// 				i = 0;
// 				while (i < table->nbr_philo)
// 				{
// 					pthread_detach(table->philos[i].thread_id);
// 					i++;
// 				}
// 			}
// 			i++;
// 		}

// 	}
// }

	// 	pthread_mutex_lock(philo->table->thread_dead);
	// 	if (philo->table->one_philo_dead == 1)
	// 	{
	// 		pthread_mutex_lock(philo->table->thread_printf);
	// 		my_printf(philo, "is dead");
	// 		pthread_mutex_unlock(philo->table->thread_printf);
	// 		pthread_mutex_unlock(philo->table->thread_dead);
	// 		pthread_mutex_unlock(philo->table->thread_check_meal);
	// 		return (0);
	// 	} 
	// pthread_mutex_unlock(philo->table->thread_dead);