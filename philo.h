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
	long end_simulation; //Philo died or nbr_limit_meals surpassed
	int one_philo_dead;
	long start_dinner_time;
	


	t_philo *philos;
	t_mtx *thread_dead;
	t_mtx *thread_start_dinner_time;



}		t_table;

typedef struct s_philo
{
	int id;
	int full;
	long time_last_meal;
	long meal_counter;
	pthread_t thread_id;

	t_mtx left_fork;
	int  left_fork_id;

	t_mtx right_fork;
	int  right_fork_id;
	t_table *table;


}		t_philo;


// FUNCTIONS :

// MAIN.C

int init_struct(t_table *table, int argc, char **argv);
int	init_philos(t_table *table);
long ft_atol(char *str);

// DINNER_START.C
void dinner_start(t_table *table);
void *dinner_simulation(void *data);

// CHECK_ARGS.C
int contains_a_digit(char *str);
int check_arguments(int argc, char **argv);


// TIME.C : 
int set_timer();

#endif