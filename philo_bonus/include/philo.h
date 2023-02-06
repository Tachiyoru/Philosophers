/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:33:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/06 12:08:46 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>

# define EATING			" is eating\n"
# define SLEEPING		" is sleeping\n"
# define THINKING		" is thinking\n"
# define TAKEN_FORK		" has taken a fork\n"
# define PHILO_DIED		" died\n"

# define NC			"\e[0m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define BLUE		"\e[34m"
# define BRED		"\e[1;31m"

typedef struct s_life
{
	long		time_death;
	long		time_sleep;
	long		time_eat;
	int			need_eating;
	int			smbdy_died;
	long long	start;
	sem_t		*dead;
	sem_t		*fork;
	sem_t		*time;
	sem_t		*eat;
	sem_t		*write;
}t_life;

typedef struct s_philos
{
	int			nbr;
	int			has_eaten;
	long long	dying;
	pthread_t	checker;
	t_life		*life;
}t_philos;

typedef struct s_data
{
	t_life		life;
	int			nbr_philo;
	int			pid[200];
	t_philos	philos[200];
}t_data;

///Main
int			main(int argc, char **argv);
void		solitary(char **argv);

///Parsing
int			check_args(int argc, char **argv);
int			only_numbers(char **argv, int argc);

///Init
int			init(t_data *data, char **argv);
int			semaphore_init(t_data *data);

///Make philo
int			make_philo(t_data *data);
int			ft_waitpid_kill(t_data *data);
int			kill_process_until(t_data *data, int until);

///Life
int			life(t_philos *philo1, t_data *data);
// int			any_dead(t_philos *philo1, t_data *data);
int			life_line(t_philos *philo1, t_data *data);

///Lifeline

int			any_dead(t_philos *philo1, t_data *data);
int			philo_eat(t_philos *philo1, t_data *data);
int			philo_sleep(t_philos *philo1, t_data *data);
int			philo_think(t_philos *philo1, t_data *data);

///Checker
void		*check_dead(void *data);
int			has_eaten(t_philos *philo);
int			any_dead2(t_philos *philo1);

///Time
void		ft_sleep_lifeline(t_philos *philo, t_data *data,
				long int time_in_ms);
void		ft_usleep(t_data *data, long int time_in_ms);
long long	get_time_since_start(long long time_to_wait);
long long	get_time(void);

///Utils
int			ft_write_status(t_philos *philo1, t_data *data,
				char *action, char *color);
void		destroy_semaphore(t_data *data);
void		msg(char *str);
int			ft_atoi(char *str);

#endif
