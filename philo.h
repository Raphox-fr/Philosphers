#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_table
{
	long nbr_philo;
	long time_to_eat;
	long time_to_sleep;
	long time_to_die;
	long nbr_limit_meals;
	t_philo *philos;
	long start_simulation;
	long end_simulation; //Philo died or nbr_limit_meals surpassed

}		t_table;

typedef struct s_philo
{
	int id;
	long meal_counter;
	int full;

	t_mtx left_fork;
	int  left_fork_id;

	t_mtx right_fork;
	int  right_fork_id;
	t_table *table;


}		t_philo;


// FUNCTIONS :

// Main.c

int init_struct(t_table *table, int argc, char **argv);
long ft_atol(char *str);



// Check_args :
int contains_a_digit(char *str);
int check_arguments(int argc, char **argv);



#endif