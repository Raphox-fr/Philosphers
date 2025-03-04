/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:50:02 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/04 16:31:15 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	i = 0;
	if (argc == 0)
		return (0);
	if (check_arguments(argc, argv) == -1)
		return (-1);
	if (init_struct(&table, argc, argv) == -1)
		return (-1);
	if (dinner_start(&table) == -1)
	{
		return (-1);
	}
	return (0);
}
