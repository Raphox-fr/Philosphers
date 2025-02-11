/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:28:46 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 15:44:39 by rafaria          ###   ########.fr       */
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


void assign_forks(t_philo *philo, int philo_position)
{
	int i;
	i = 0;


	t_mtx fork;
	int nbr_philo;

	nbr_philo = philo->table->nbr_philo;

	philo->thread_left_fork = &fork;
	philo->left_fork_id = ((philo_position + 1) % nbr_philo);
	philo->thread_left_fork = &fork;
	philo->right_fork_id = (philo_position);

	if (philo->id % 2 == 0) // pair
	{
		philo->thread_right_fork = &fork;
		philo->left_fork_id = (philo_position);
		philo->thread_right_fork = &fork;
		philo->right_fork_id = ((philo_position + 1) % nbr_philo);
	}
}




