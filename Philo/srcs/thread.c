/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:12:31 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 16:07:54 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	any_dead(t_philos *philo1)
{
	long long	time;

	time = get_time_since_start(philo1->life->start);
	pthread_mutex_lock(&philo1->life->dead);
	if (philo1->life->smbdy_died == 1)
		return (pthread_mutex_unlock(&philo1->life->dead), 1);
	pthread_mutex_unlock(&philo1->life->dead);
	if (philo1->life->time_death < (time - philo1->dying))
	{
		pthread_mutex_lock(&philo1->life->write);
		pthread_mutex_lock(&philo1->life->dead);
		philo1->life->smbdy_died = 1;
		pthread_mutex_unlock(&philo1->life->dead);
		printf(BRED"%lld	%d is dead\n"NC,
			get_time_since_start(philo1->life->start), philo1->nbr);
		pthread_mutex_unlock(&philo1->life->write);
		return (1);
	}
	return (0);
}

int	life_line(t_philos *philo1)
{
	if (any_dead(philo1))
		return (1);
	if (philo_fork(philo1))
		return (1);
	if (any_dead(philo1))
		return (1);
	if (philo_eat(philo1))
		return (1);
	if (any_dead(philo1))
		return (1);
	if (philo_sleep(philo1))
		return (1);
	if (any_dead(philo1))
		return (1);
	if (philo_think(philo1))
		return (1);
	if (any_dead(philo1))
		return (1);
	return (0);
}

void	*life(void	*s1)
{
	t_philos	*philo1;

	philo1 = (t_philos *)s1;
	while (!any_dead(philo1) && (!philo1->life->need_eating
			|| philo1->has_eaten < philo1->life->need_eating))
		if (life_line(philo1))
			return (NULL);
	return (NULL);
}

int	make_thread(t_data *data)
{
	int			i;

	i = 0;
	data->life.start = get_time();
	if (pthread_create(&data->checker, NULL, check_dead, (void *)data))
		return (msg("Error while creating checker thread"), 1);
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				life, &data->philos[i]))
			return (0);
		i += 2;
		if (i >= data->nbr_philo && i % 2 == 0)
		{
			i = 1;
			ft_usleep(&data->philos[i], 2);
		}
	}
	if (!join_threads(data))
		return (0);
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_join(data->checker, NULL))
		return (msg("Error in pthread join for checker\n"), 0);
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (msg("Error in pthread join for philo\n"), 0);
	}
	usleep(1000);
	return (1);
}
