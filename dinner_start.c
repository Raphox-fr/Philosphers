/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/24 16:04:25 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include <unistd.h>


int pick_up_the_forks(t_philo *philo)
{
	// printf("ici : %d \n", philo->id + 1);
	if (philo->id % 2 == 0) // est pair
	{
		pthread_mutex_lock(philo->thread_right_fork);
		pthread_mutex_lock(philo->thread_left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->thread_right_fork);
		pthread_mutex_lock(philo->thread_left_fork);	
	}
	return (1);
}

int release_the_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) // est pair
	{
		pthread_mutex_unlock(philo->thread_right_fork);
		pthread_mutex_unlock(philo->thread_left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->thread_left_fork);
		pthread_mutex_unlock(philo->thread_right_fork);
	}
	return (1);
}

int check_end_simulation(t_philo *philo)
{
	pthread_mutex_lock(philo->table->thread_global);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(philo->table->thread_global);
		return (0);
	}
	pthread_mutex_unlock(philo->table->thread_global);
	return (1);
}

int is_philo_dead(t_philo *philo)
{
	if (check_end_simulation(philo) == 0)
		return (0);
	return (1);

}


int go_eat(t_philo *philo)
{
	if (check_end_simulation(philo) == 0)
		return (0);
	pick_up_the_forks(philo);
	if (check_end_simulation(philo) == 0)
		return (release_the_forks(philo), 0);
	my_printf(philo, "has taken a fork", 0);	
	pthread_mutex_lock(philo->table->thread_global);
	philo->time_last_meal = set_timer();
	philo->meal_counter = philo->meal_counter + 1;
	pthread_mutex_unlock(philo->table->thread_global);
	if (check_end_simulation(philo) == 0)
		return (release_the_forks(philo), 0);
	my_printf(philo, "is eating", 0);
	if (check_end_simulation(philo) == 0)
		return (release_the_forks(philo), 0);
	usleep(philo->table->time_to_eat);
	if (check_end_simulation(philo) == 0)
		return (release_the_forks(philo), 0);
	release_the_forks(philo);
	return (1);
}

int go_sleep(t_philo *philo)
{
	if (check_end_simulation(philo) == 0)
		return (0);
	my_printf(philo, "is sleeping", 0);
	usleep(philo->table->time_to_sleep);
	return (1);
}

int go_think(t_philo *philo)
{
	if (check_end_simulation(philo) == 0)
		return (0);
	my_printf(philo, "is thinking", 0);
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

	pthread_t watch;
	
	if (table->nbr_limit_meals == 0)
		return ;
	else
	{
		pthread_create(&watch, NULL, &watch_simulation, table);
		table->start_dinner_time = set_timer();
		while (i < table->nbr_philo)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
		pthread_join(watch, NULL);
		i = 0;
		while (i < table->nbr_philo)
		{
			pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}
	}
	pthread_mutex_destroy(&table->thread_printf);
}

void *watch_simulation(void *data)
{
	t_table *table;
	table = (t_table *)data;

	long i;
	i = 0;

	int count;
	count = 0;

	while (42)
	{
		while (i < table->nbr_philo)
		{
			pthread_mutex_lock(table->thread_global);
			if (is_philo_full(table, i) == 1)
				count = count + 1;
			if (is_time_surpassed(table, i) == 1)
			{
				table->end_simulation = 1;
				my_printf(&table->philos[i], "is dead (too much time)", 0);
				pthread_mutex_unlock(table->thread_global);			
				return (NULL);				
			}		
			if (count == table->nbr_philo)
			{
				table->end_simulation = 1;
				my_printf(&table->philos[i], "limit meal atteinte", 0);
				pthread_mutex_unlock(table->thread_global);
				return (NULL);
			}
			pthread_mutex_unlock(table->thread_global);
			i++;
		}
		i = 0;
		count = 0;
		
	}
}
int is_time_surpassed(t_table *table, int i)
{
	if (table->philos[i].time_last_meal != -1 && ((set_timer() - table->philos[i].time_last_meal) * 1000) > table->time_to_die)
		return (1);
	return (0);
}



int is_philo_full(t_table *table, int i)
{
	if (table->nbr_limit_meals != -1 && table->philos[i].meal_counter >= table->nbr_limit_meals)
		return (1);
	return (0);
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

	// 	pthread_mutex_lock(philo->table->thread_global);
	// 	if (philo->table->one_philo_dead == 1)
	// 	{
	// 		pthread_mutex_lock(philo->table->thread_printf);
	// 		my_printf(philo, "is dead");
	// 		pthread_mutex_unlock(philo->table->thread_printf);
	// 		pthread_mutex_unlock(philo->table->thread_global);
	// 		pthread_mutex_unlock(philo->table->thread_check_meal);
	// 		return (0);
	// 	} 
	// pthread_mutex_unlock(philo->table->thread_global);