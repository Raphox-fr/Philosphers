/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:46 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/04 17:14:42 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	nbr;
	int		negatif;

	i = 0;
	nbr = 0;
	while ((str[i] < '0' || str[i] > '9') || ((str[i] >= 9 && str[i] <= 13)
			&& (str[i] != '-' && str[i] != '+')))
		i++;
	if (str[i - 1] == '-')
	{
		negatif = -1;
	}
	else
		negatif = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	nbr = nbr * negatif;
	return (nbr);
}

void	one_philo_table(t_table *table)
{
	table->start_dinner_time = set_timer();
	if (pthread_create(&table->philos[0].thread_id, NULL, dinner_simulation,
			&table->philos[0]) != 0)
	{
		return (destroy_all(table));
	}
	my_printf(&table->philos[0], "has taken a fork", 0);
	ft_usleep(table->time_to_die, table);
	my_printf(&table->philos[0], "is dead", 0);
	if (pthread_join(table->philos[0].thread_id, NULL) != 0)
	{
		return (destroy_all(table));
	}
}

int	destroy_forks(t_table *table)
{
	pthread_mutex_destroy(table->thread_forks);
	return (-1);
}

void	print_trinite(t_philo *philo)
{
	my_printf(philo, "has taken a fork", 0);
	my_printf(philo, "has taken a fork", 0);
	my_printf(philo, "is eating", 0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->thread_forks[i], NULL) != 0)
		{
			destroy_forks(table);
			return (-1);
		}
		i++;
	}
	return (0);
}
