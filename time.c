/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:44 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/11 11:49:58 by rafaria          ###   ########.fr       */
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