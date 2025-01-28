/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:50:02 by rafaria           #+#    #+#             */
/*   Updated: 2025/01/28 18:24:01 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>


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

int check_arguments(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;

	while (argv[i] != NULL)
	{
		if (contains_a_digit(argv[i]) == 0)
		{
			write(2, "Error: arguments contain numeric character\n", 43);
			return (0);
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int i;
	i = 0;

	check_arguments(argv);
	return (0);

}