/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:37:41 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 16:13:31 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	has_eaten(t_data *data, int i)
{
	pthread_mutex_lock(&data->life.eat);
	if (data->philos[i].has_eaten < data->life.need_eating)
	{
		pthread_mutex_unlock(&data->life.eat);
		return (0);
	}
	pthread_mutex_unlock(&data->life.eat);
	return (1);
}

int	any_dead2(t_data *data)
{
	pthread_mutex_lock(&data->life.dead);
	if (data->life.smbdy_died == 1)
		return (pthread_mutex_unlock(&data->life.dead), 1);
	pthread_mutex_unlock(&data->life.dead);
	return (0);
}

void	*check_dead(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	while (!any_dead2(data) && (!data->life.need_eating
			|| !has_eaten(data, i)))
	{
		if (is_philo_dead(data, i))
			return (NULL);
		i++;
		if (i == data->nbr_philo)
			i = 0;
	}
	return (NULL);
}

int	is_philo_dead(t_data *data, int i)
{
	long long	time;

	pthread_mutex_lock(&data->life.time);
	time = get_time_since_start(data->life.start);
	if (data->life.time_death < (time - data->philos[i].dying))
	{
		pthread_mutex_lock(&data->life.dead);
		data->life.smbdy_died = 1;
		pthread_mutex_unlock(&data->life.dead);
		pthread_mutex_lock(&data->life.write);
		printf(BRED"%lld	%d is dead\n"NC,
			get_time_since_start(data->life.start), data->philos[i].nbr);
		pthread_mutex_unlock(&data->life.write);
		pthread_mutex_unlock(&data->life.time);
		return (1);
	}
	pthread_mutex_unlock(&data->life.time);
	ft_usleep2(data, 1);
	return (0);
}
