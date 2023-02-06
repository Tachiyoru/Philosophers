/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:09:05 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 16:02:42 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	solitary(char **arg)
{
	int	life;

	life = ft_atoi(arg[1]);
	printf("0	1 %s", TAKEN_FORK);
	usleep(life * 1000);
	printf(BRED"%d	1 %s"NC, life, PHILO_DIED);
}

int	philo_fork(t_philos *philo1)
{
	if (philo1->nbr == 1)
	{
		pthread_mutex_lock(philo1->left_fork);
		if (ft_write_status(philo1, TAKEN_FORK, NC))
			return (pthread_mutex_unlock(philo1->left_fork), 1);
		pthread_mutex_lock(philo1->right_fork);
		if (ft_write_status(philo1, TAKEN_FORK, NC))
			return (pthread_mutex_unlock(philo1->right_fork)
				, pthread_mutex_unlock(philo1->left_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo1->right_fork);
		if (ft_write_status(philo1, TAKEN_FORK, NC))
			return (pthread_mutex_unlock(philo1->right_fork), 1);
		pthread_mutex_lock(philo1->left_fork);
		if (ft_write_status(philo1, TAKEN_FORK, NC))
			return (pthread_mutex_unlock(philo1->left_fork)
				, pthread_mutex_unlock(philo1->right_fork), 1);
	}
	return (0);
}

int	philo_eat(t_philos *philo1)
{
	if (ft_write_status(philo1, EATING, GREEN))
		return (pthread_mutex_unlock(philo1->right_fork)
			, pthread_mutex_unlock(philo1->left_fork), 1);
	pthread_mutex_lock(&philo1->life->time);
	philo1->dying = get_time_since_start(philo1->life->start);
	pthread_mutex_unlock(&philo1->life->time);
	ft_usleep(philo1, philo1->life->time_eat);
	pthread_mutex_lock(&philo1->life->eat);
	philo1->has_eaten++;
	pthread_mutex_unlock(&philo1->life->eat);
	pthread_mutex_unlock(philo1->left_fork);
	pthread_mutex_unlock(philo1->right_fork);
	return (0);
}

int	philo_sleep(t_philos *philo1)
{
	if (ft_write_status(philo1, SLEEPING, BLUE))
		return (1);
	ft_usleep(philo1, philo1->life->time_sleep);
	return (0);
}

int	philo_think(t_philos *philo1)
{
	if (ft_write_status(philo1, THINKING, NC))
		return (1);
	return (0);
}
