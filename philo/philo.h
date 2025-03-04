/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaria <rafaria@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:20:36 by rafaria           #+#    #+#             */
/*   Updated: 2025/03/04 16:38:06 by rafaria          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	long				nbr_philo;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_die;
	long				nbr_limit_meals;
	long				end_simulation;
	long				one_philo_dead;
	long				start_dinner_time;

	t_philo				*philos;
	pthread_mutex_t		*thrd_gbl;

	pthread_mutex_t		thread_printf;
	pthread_mutex_t		*thread_forks;

}						t_table;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meal_counter;
	long				time_last_meal;

	pthread_t			thread_id;
	pthread_mutex_t		*thread_l_fork;
	pthread_mutex_t		*thread_r_fork;

	t_table				*table;
}						t_philo;

// FUNCTIONS :

// MAIN.C

int						init_struct(t_table *table, int argc, char **argv);
int						init_philos(t_table *table);
long					ft_atol(char *str);

// DINNER_START.C
int						dinner_start(t_table *table);
void					*dinner_simulation(void *data);
void					*watch_simulation(void *data);

// CHECK_ARGS.C
int						contains_a_digit(char *str);
int						check_arguments(int argc, char **argv);

// INIT . C
void					assign_forks(t_table *table, int philo_position);

// TIME.C :
long					set_timer(void);
void					my_printf(t_philo *philo, char *str, int i);

// FORKS

int						release_the_forks(t_philo *philo);
int						pick_up_the_forks(t_philo *philo);

int						init_forks(t_table *table);
int						destroy_forks(t_table *table, int i);
int						destroy_all_forks(t_table *table);

int						is_philo_full(t_table *table, int i);

int						ft_usleep(long time, t_table *table);

int						is_time_surpassed(t_table *table, int i);

int						is_philo_dead(t_philo *philo);

void					one_philo_table(t_table *table);

char					check_all(t_table *table, int i, int count);

void					destroy_all(t_table *table, int i);

void					print_trinite(t_philo *philo);

int						dinner_start_2(t_table *table);

#endif