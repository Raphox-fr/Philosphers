/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:59:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/04 17:15:02 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_the_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->thread_r_fork);
		pthread_mutex_lock(philo->thread_l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->thread_l_fork);
		pthread_mutex_lock(philo->thread_r_fork);
	}
	return (1);
}

int	release_the_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->thread_l_fork);
		pthread_mutex_unlock(philo->thread_r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->thread_r_fork);
		pthread_mutex_unlock(philo->thread_l_fork);
	}
	return (1);
}

int	is_philo_dead()
{
	return (1);
}

int	dinner_start_2(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			return (destroy_all(table), -1);
		i++;
	}
	return (0);
}

void	destroy_all(t_table *table)
{
	pthread_mutex_destroy(table->thrd_gbl);
	pthread_mutex_destroy(&table->thread_printf);
	pthread_mutex_destroy(table->thread_forks);
	free(table->philos);
	free(table->thrd_gbl);
	free(table->thread_forks);
}
