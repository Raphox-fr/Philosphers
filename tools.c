/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:46 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/06 18:14:28 by rafaria          ###   ########.fr       */
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
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
	if ((table->time_to_die < 6000)
		|| (table->time_to_eat < 6000)
		|| (table->time_to_sleep < 6000))
		{
			return (0); // ERROR
		}
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philo);
	if (table->philos)
		return (0); // ERROR	
	return (0);	
}

void assign_forks(t_philo *philo, int philo_position)
{
	int i;
	i = 0;


	t_mtx fork;
	int nbr_philo;

	nbr_philo = philo->table->nbr_philo;

	philo->left_fork = fork;
	philo->left_fork_id = ((philo_position + 1) % nbr_philo);
	philo->right_fork = fork;
	philo->right_fork_id = (philo_position);

	if (philo->id % 2 == 0) // pair
	{
		philo->left_fork = fork;
		philo->left_fork_id = (philo_position);
		philo->right_fork = fork;
		philo->right_fork_id = ((philo_position + 1) % nbr_philo);
	}
}
int	init_philos(t_table *table)
{
	int i;
	i = 0;

	while (i < table->nbr_philo)
	{
		table->philos[i].id = i;
		table->philos[i].full = false;
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		assign_forks(&table->philos[i], i);
		i++;
	}
	return (0);
}



