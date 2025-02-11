/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:50:02 by rafaria           #+#    #+#             */
/*   Updated: 2025/02/06 18:15:50 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philo.h"



int main(int argc, char **argv)
{
	int i;
	t_table table;

	i = 0;
	if (check_arguments(argc, argv) == -1)
		return (0);

	init_struct(&table, argc, argv);
	dinner_start(&table);
	return (0);
}




	// printf("%ld", ft_atol(argv[1]));