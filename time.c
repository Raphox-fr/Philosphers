/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/24 17:29:11 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long set_timer()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void my_printf(t_philo *philo, char *str, int i)
{	
	pthread_mutex_lock(&philo->table->thread_printf);
	if (i == 1)
	{
		printf("%s", str);
		pthread_mutex_unlock(&philo->table->thread_printf);	
		return ;
	}
	printf("%ld  %d  %s\n", set_timer() - philo->table->start_dinner_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->table->thread_printf);	

}