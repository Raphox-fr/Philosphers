/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:46 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/28 12:28:35 by rafaria          ###   ########.fr       */
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
	pthread_create(&table->philos[0].thread_id, NULL, dinner_simulation,
		&table->philos[0]);
	my_printf(&table->philos[0], "has taken a fork", 0);
	ft_usleep(table->time_to_die, table);
	my_printf(&table->philos[0], "is dead", 0);
	pthread_join(table->philos[0].thread_id, NULL);
}
