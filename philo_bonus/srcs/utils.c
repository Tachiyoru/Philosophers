/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:36:18 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_write_status(t_philos *philo1, t_data *data, char *action, char *color)
{
	long long	time;

	time = get_time_since_start(philo1->life->start);
	if (any_dead(philo1, data))
		return (1);
	sem_wait(philo1->life->write);
	printf("%s%lli\t%d %s"NC, color, time, philo1->nbr, action);
	sem_post(philo1->life->write);
	return (0);
}

void	destroy_semaphore(t_data *data)
{
	sem_close(data->life.write);
	sem_unlink("/writing_sem");
	sem_close(data->life.fork);
	sem_unlink("/fork_sem");
	sem_close(data->life.time);
	sem_unlink("/time_sem");
	sem_close(data->life.eat);
	sem_unlink("/eat_sem");
	sem_close(data->life.dead);
	sem_unlink("/dead_sem");
}

void	msg(char *str)
{
	printf("%s", str);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result *= sign);
}
