/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:54:43 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	life(t_philos *philo1, t_data *data)
{
	while (!any_dead(philo1, data) && (!philo1->life->need_eating
			|| philo1->has_eaten < philo1->life->need_eating))
	{
		if (life_line(philo1, data))
		{
			usleep(1000);
			destroy_semaphore(data);
			exit (1);
		}
	}
	if (any_dead(philo1, data))
	{
		usleep(1000);
		destroy_semaphore(data);
		exit (1);
	}
	pthread_detach(philo1->checker);
	destroy_semaphore(data);
	exit (0);
}

int	life_line(t_philos *philo1, t_data *data)
{
	if (pthread_create(&philo1->checker, NULL, check_dead, philo1))
		return (msg("Error in checker thread create \n"), 1);
	if (any_dead(philo1, data))
		return (pthread_detach(philo1->checker), 2);
	if (philo_eat(philo1, data))
		return (pthread_detach(philo1->checker), 3);
	if (any_dead(philo1, data))
		return (pthread_detach(philo1->checker), 2);
	if (philo_sleep(philo1, data))
		return (pthread_detach(philo1->checker), 4);
	if (any_dead(philo1, data))
		return (pthread_detach(philo1->checker), 2);
	if (philo_think(philo1, data))
		return (pthread_detach(philo1->checker), 5);
	if (any_dead(philo1, data))
		return (pthread_detach(philo1->checker), 2);
	return (0);
}
