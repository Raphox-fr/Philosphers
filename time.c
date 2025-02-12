/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/12 16:48:15 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long set_timer()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void my_printf(t_philo *philo, char *str)
{
	printf("time : %ld |", set_timer() - philo->table->start_dinner_time);
	printf("   ");
	printf("id : %d", philo->id);
	printf("   ");
	printf("%s", str);
	printf("\n");	

}