/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:50:02 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/06 15:27:54 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 1)
	{
		printf("Needs arguments\n");
		return (-1);
	}
	if (check_arguments(argc, argv) == -1)
		return (-1);
	if (init_struct(&table, argv) == -1)
		return (-1);
	if (dinner_start(&table) == -1)
	{
		return (-1);
	}
	return (0);
}
