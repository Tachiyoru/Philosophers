/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:19:52 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_dead(void *data)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = (t_philos *)data;
	while (!any_dead2(philo)
		&& (!philo->life->need_eating || !has_eaten(philo)))
	{
		if (any_dead2(philo))
			return (pthread_detach(philo->checker), NULL);
	}
	pthread_detach(philo->checker);
	return (NULL);
}

int	any_dead2(t_philos *philo1)
{
	long long	time;

	sem_wait(philo1->life->time);
	time = get_time_since_start(philo1->life->start);
	sem_post(philo1->life->time);
	sem_wait(philo1->life->dead);
	if (philo1->life->smbdy_died == 1)
		return (sem_post(philo1->life->dead), 1);
	sem_post(philo1->life->dead);
	sem_wait(philo1->life->time);
	if (philo1->life->time_death < (time - philo1->dying))
	{
		sem_post(philo1->life->time);
		sem_wait(philo1->life->dead);
		philo1->life->smbdy_died = 1;
		sem_post(philo1->life->dead);
		sem_wait(philo1->life->write);
		printf(BRED"%lld	%d is dead\n"NC,
			get_time_since_start(philo1->life->start), philo1->nbr);
		return (1);
	}
	pthread_detach(philo1->checker);
	sem_post(philo1->life->time);
	usleep(20000);
	return (0);
}

int	has_eaten(t_philos *philo)
{
	sem_wait(philo->life->eat);
	if (philo->has_eaten >= philo->life->need_eating)
	{
		sem_post(philo->life->eat);
		return (1);
	}
	sem_post(philo->life->eat);
	return (0);
}
