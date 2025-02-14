/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/14 18:47:06 by rafaria          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->table->thread_printf);
	printf("%ld", set_timer() - philo->table->start_dinner_time);
	printf("  ");
	printf("%d", philo->id);
	printf("  ");
	printf("%s", str);
	printf("\n");
	pthread_mutex_unlock(&philo->table->thread_printf);	

}