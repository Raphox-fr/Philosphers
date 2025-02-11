/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:14:20 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 10:24:47 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philo.h"
void* dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;


	while (is_philo_dead(	))

	

	

	
	

	

	
	return (NULL);
	
	
}



void dinner_start(t_table *table)
{
	int i;
	i = 0;
	
	
	if (table->nbr_limit_meals == 0)
		return ;
	if (table->nbr_philo == 1)
		return ;
	else
	{
		while (i < table->nbr_philo)
		{
			printf("valeur i %d\n", i);
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	
	
}