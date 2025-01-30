/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:46 by rafaria           #+#    #+#             */
/*   Updated: 2025/01/30 13:19:10 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


long ft_atol(char *str)
{
	int i;
	long nbr;
	int negatif;

	i = 0;
	nbr = 0;

	while ((str[i] < '0' || str[i] > '9') || (str[i] >= 9 && str[i] <= 13) && (str[i] != '-' && str[i] != '+'))
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




int init_struct(t_table *table, int argc, char **argv)
{
	int i;
	i = 0;

	table->nbr_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;		

	return (0);
	
}