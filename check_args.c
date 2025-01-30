/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:30:40 by rafaria           #+#    #+#             */
/*   Updated: 2025/01/30 13:10:08 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int contains_a_digit(char *str)
{
	int i;
	i = 0;

	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '\0'))
			return (0);
		i++;
	}
	return (1);
}

int check_arguments(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;

	if (argc < 5 || argc > 6)
	{
		printf("Error: not enough or too many arguments\n");
		return (-1);
	}
	while (argv[i] != NULL)
	{
		if (contains_a_digit(argv[i]) == 0)
		{
			printf("Error: arguments contain numeric character\n");
			return (-1);
		}
		i++;
	}
	return (1);
}