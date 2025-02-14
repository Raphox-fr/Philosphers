/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/14 16:13:37 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <unistd.h>

int is_philo_dead(t_philo *philo)
{
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
	return (1);
}

int go_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);

	pthread_mutex_lock(philo->table->thread_dead);
	pthread_mutex_lock(philo->table->thread_last_time_meal);
	philo->time_last_meal = set_timer();
	philo->meal_counter = philo->meal_counter + 1;
	if (philo->table->end_simulation == 1)
	{
		write(1, "END SIMULATION\n", 15);
		pthread_mutex_unlock(philo->table->thread_dead);
		pthread_mutex_unlock(philo->table->thread_last_time_meal);

		return (0);
	}
	pthread_mutex_unlock(philo->table->thread_last_time_meal);
	pthread_mutex_unlock(philo->table->thread_dead);
	
	pthread_mutex_lock(philo->table->thread_printf);
	my_printf(philo, "is eating");
	pthread_mutex_unlock(philo->table->thread_printf);

	usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->thread_lock_meal);
	
	return (1);
}

int go_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);

	pthread_mutex_lock(philo->table->thread_dead);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thread_dead);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thread_dead);
	pthread_mutex_lock(philo->table->thread_printf);			
	my_printf(philo, "is sleeping");
	pthread_mutex_unlock(philo->table->thread_printf);
	usleep(philo->table->time_to_sleep);;
	pthread_mutex_unlock(philo->thread_lock_meal);

	return (1);
}

int go_think(t_philo *philo)
{
	pthread_mutex_lock(philo->thread_lock_meal);

	pthread_mutex_lock(philo->table->thread_dead);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thread_dead);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thread_dead);
	pthread_mutex_lock(philo->table->thread_printf);
	my_printf(philo, "is thinking");
	pthread_mutex_unlock(philo->table->thread_printf);
	
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
	if (pthread_create(&watch, NULL, &watch_simulation, table) == 0)
		pthread_detach(watch);
		
		while (i < table->nbr_philo)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
		if (pthread_join(watch, NULL) == 0)
				pthread_detach(watch);		
		i = 0;
		while (i < table->nbr_philo)
		{
			pthread_join(table->philos[i].thread_id, NULL);

			i++;
		}
	}
}

void *watch_simulation(void *data)
{
	t_table *table;
	table = (t_table *)data;

	long i;
	i = 0;

	long pin;
	pin = 0;

	while (table->end_simulation != 1)
	{
		i = 0; 
		while (i < table->nbr_philo)
		{
			pthread_mutex_lock(table->thread_dead);
			if (table->philos[i].meal_counter == table->nbr_limit_meals && table->nbr_limit_meals != -1)
			{
				pin++;
				if (pin == table->nbr_philo - 1)
				{
					table->end_simulation = 1;
					pthread_mutex_lock(table->philos->table->thread_printf);
					printf("EVERYBODY IS FULL\n");
					pthread_mutex_unlock(table->philos->table->thread_printf);
					pthread_mutex_unlock(table->thread_dead);
					exit(0);
				}
			}
			pthread_mutex_lock(table->thread_last_time_meal);
			if (table->philos[i].time_last_meal != -1 && ((set_timer() - table->philos[i].time_last_meal) * 1000) > table->time_to_die)
			{
				table->end_simulation = 1;
				pthread_mutex_lock(table->philos->table->thread_printf);
				my_printf(&table->philos[i], "is dead");
				pthread_mutex_unlock(table->philos->table->thread_printf);
				pthread_mutex_unlock(table->thread_dead);
				pthread_mutex_unlock(table->thread_last_time_meal);
				exit(0);
			}
			pthread_mutex_unlock(table->thread_last_time_meal);

			pthread_mutex_unlock(table->thread_dead);
			usleep(100);
			i++;
		}
		pin = 0;
	}
	return (NULL);
}


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