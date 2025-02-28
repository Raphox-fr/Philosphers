/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:59:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/28 12:12:42 by rafaria          ###   ########.fr       */
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

int	is_philo_dead(t_philo *philo)
{
	return (1);
}
