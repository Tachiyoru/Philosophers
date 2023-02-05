/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:15:50 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	any_dead(t_philos *philo1, t_data *data)
{
	long long	time;

	(void)data;
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
	sem_post(philo1->life->time);
	return (0);
}

int	philo_eat(t_philos *philo1, t_data *data)
{
	sem_wait(philo1->life->fork);
	if (ft_write_status(philo1, data, TAKEN_FORK, NC))
		return (1);
	sem_wait(philo1->life->fork);
	if (ft_write_status(philo1, data, TAKEN_FORK, NC))
		return (1);
	if (ft_write_status(philo1, data, EATING, GREEN))
		return (1);
	sem_wait(philo1->life->time);
	philo1->dying = get_time_since_start(philo1->life->start);
	sem_post(philo1->life->time);
	ft_sleep_lifeline(philo1, data, philo1->life->time_eat);
	sem_wait(philo1->life->eat);
	philo1->has_eaten++;
	sem_post(philo1->life->eat);
	sem_post(philo1->life->fork);
	sem_post(philo1->life->fork);
	return (0);
}

int	philo_sleep(t_philos *philo1, t_data *data)
{
	if (ft_write_status(philo1, data, SLEEPING, BLUE))
		return (1);
	ft_sleep_lifeline(philo1, data, philo1->life->time_sleep);
	return (0);
}

int	philo_think(t_philos *philo1, t_data *data)
{
	if (ft_write_status(philo1, data, THINKING, NC))
		return (1);
	return (0);
}
