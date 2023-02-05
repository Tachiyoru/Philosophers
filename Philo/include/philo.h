/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:44:40 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 16:10:08 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	long				time_death;
	long				time_sleep;
	long				time_eat;
	int					need_eating;
	int					smbdy_died;
	long long			start;
	pthread_mutex_t		dead;
	pthread_mutex_t		fork;
	pthread_mutex_t		time;
	pthread_mutex_t		eat;
	pthread_mutex_t		write;
}t_life;

typedef struct s_philos
{
	int				nbr;
	int				has_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		dying;
	t_life			*life;
	pthread_t		thread;
}t_philos;

typedef struct s_data
{
	t_life		life;
	int			nbr_philo;
	t_philos	philos[200];
	pthread_t	checker;
}t_data;

		//////checker//////
int			is_philo_dead(t_data *data, int i);
int			has_eaten(t_data *data, int i);
void		*check_dead(void *arg);

		//////time//////
void		ft_usleep2(t_data *data, long int time_in_ms);
void		ft_usleep(t_philos *data, long int time_in_ms);
long long	get_time(void);
long long	get_time_since_start(long long time_to_wait);

		//////utils//////
int			ft_strncmp(const char *a, const char *b, size_t l);
int			ft_atoi(char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		msg(char *str);

		//////life.c//////
void		solitary(char **arg);
int			philo_fork(t_philos *philo1);
int			philo_eat(t_philos *philo1);
int			philo_sleep(t_philos *philo1);
int			philo_think(t_philos *philo1);

		//////thread.c//////
int			life_line(t_philos *philo1);
void		*life(void	*s1);
int			join_threads(t_data *data);
int			make_thread(t_data *data);
int			any_dead(t_philos *philo1);

		//////init.c//////
void		destroy_all(t_data *data);
int			init(t_data *data, char **argv);
int			make_philo(t_data *data);
int			make_forks(t_data *data);

		//////main.c//////
int			main(int argc, char **argv);
int			ft_write_status(t_philos *data, char *action, char *color);

#endif
