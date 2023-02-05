/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:50:36 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long	get_time_since_start(long long time_to_wait)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (time_to_wait > 0)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - time_to_wait);
	return (0);
}

void	ft_usleep(t_data *data, long int time_in_ms)
{
	long int	start_time;
	int			i;

	i = 0;
	start_time = get_time_since_start(data->life.start);
	while (get_time_since_start(data->life.start) < start_time + time_in_ms)
	{
		if (data->life.smbdy_died == 1)
			return ;
		usleep(time_in_ms / 20);
	}
}

void	ft_sleep_lifeline(t_philos *philo, t_data *data, long int time_in_ms)
{
	long int	start_time;
	int			i;

	i = 0;
	start_time = get_time_since_start(philo->life->start);
	while (get_time_since_start(philo->life->start) < start_time + time_in_ms)
	{
		if (any_dead(philo, data))
			return ;
		usleep(time_in_ms / 30);
	}
}
