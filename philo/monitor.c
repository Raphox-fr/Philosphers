/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:07:48 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/03 12:06:16 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*watch_simulation(void *data)
{
	t_table	*table;
	long	i;
	int		count;

	table = (t_table *)data;
	i = 0;
	count = 0;
	while (42)
	{
		while (i < table->nbr_philo)
		{
			pthread_mutex_lock(table->thrd_gbl);
			if (is_philo_full(table, i) == 1)
			{
				count = count + 1;
			}
			if (check_all(table, i, count) == '1')
			{
				return (NULL);
			}
			pthread_mutex_unlock(table->thrd_gbl);
			i++;
		}
		
			i = 0;
		count = 0;
	}
}

char	check_all(t_table *table, int i, int count)
{
	if (is_time_surpassed(table, i) == 1 || (count == table->nbr_philo))
	{
		table->end_simulation = 1;
		if (count != table->nbr_philo && is_time_surpassed(table, i) == 1)
			my_printf(&table->philos[i], "died", 0);
		return (pthread_mutex_unlock(table->thrd_gbl), '1');
	}
	return ('0');
}

int	is_time_surpassed(t_table *table, int i)
{
	if (table->philos[i].time_last_meal != -1 && ((set_timer()
				- table->philos[i].time_last_meal)) > table->time_to_die)
		return (1);
	return (0);
}

int	is_philo_full(t_table *table, int i)
{
	if (table->nbr_limit_meals != -1
		&& table->philos[i].meal_counter >= table->nbr_limit_meals)
	{
		table->philos[i].full = 1;
		return (1);
	}
	return (0);
}

int	ft_usleep(long time, t_table *table)
{
	long	start;

	(void)table;
	start = set_timer();
	while ((set_timer() - start) < time)
	{
		usleep(500);
	}
	return (0);
}
