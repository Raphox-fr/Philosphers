#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
 #include <unistd.h>

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
	long one_philo_dead;
	long start_dinner_time;


	t_philo *philos;
	pthread_mutex_t *thread_global;
	
	pthread_mutex_t thread_printf;
	pthread_mutex_t *thread_forks;

}		t_table;

typedef struct s_philo
{
	int id;
	int full;
	long meal_counter;
	int  *left_fork_id;
	int  *right_fork_id;
	long time_last_meal;
	
	pthread_t    thread_id;
	pthread_mutex_t *thread_left_fork;
	pthread_mutex_t *thread_right_fork;
	pthread_mutex_t *thread_lock_meal;

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
void *watch_simulation(void *data);

// CHECK_ARGS.C
int contains_a_digit(char *str);
int check_arguments(int argc, char **argv);


// INIT . C
void assign_forks(t_table *table, int philo_position);

// TIME.C : 
long set_timer();
void my_printf(t_philo *philo, char *str, int i);

// FORKS RELATED

int release_the_forks(t_philo *philo);
int pick_up_the_forks(t_philo *philo);


int is_philo_full(t_table *table, int i);

int	ft_usleep(long time, t_table *table);

int is_time_surpassed(t_table *table, int i);
// 


#endif