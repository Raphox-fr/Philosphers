/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 15:32:21 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int set_timer()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	printf("%ld\n", time.tv_sec * 1000 + time.tv_usec / 1000);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void my_printf(t_philo *philo, char *str)
{
	printf("%ld", philo->time_last_meal);
	printf("	");
	printf("%d", philo->id);
	printf("	");
	printf("%s", str);
	printf("\n");

	
}