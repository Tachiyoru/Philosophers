/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:56:27 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 13:29:52 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	make_philo(t_data *data)
{
	int	i;

	i = -1;
	if (!make_forks(data))
		return (0);
	while (++i < data->nbr_philo)
	{
		data->philos[i].life = &data->life;
		data->philos[i].dying = 0;
		data->philos[i].nbr = i + 1;
		data->philos[i].has_eaten = 0;
	}
	return (1);
}

int	make_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (data->philos[i].right_fork == NULL)
			return (destroy_all(data), msg("Error in malloc mutex fork\n"), 0);
		if (pthread_mutex_init(data->philos[i].right_fork, NULL))
			return (destroy_all(data), msg("Error in mutex init fork\n"), 0);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (i == data->nbr_philo - 1)
			data->philos[i].left_fork = data->philos[0].right_fork;
		else
			data->philos[i].left_fork = data->philos[i + 1].right_fork;
		i++;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->life.write, NULL))
		return (msg("Error in mutex init\n"), 1);
	if (pthread_mutex_init(&data->life.eat, NULL))
		return (pthread_mutex_destroy(&data->life.write),
			msg("Error in mutex init\n"), 2);
	if (pthread_mutex_init(&data->life.time, NULL))
		return (pthread_mutex_destroy(&data->life.write),
			pthread_mutex_destroy(&data->life.eat),
			msg("Error in mutex init\n"), 3);
	if (pthread_mutex_init(&data->life.dead, NULL))
		return (pthread_mutex_destroy(&data->life.write),
			pthread_mutex_destroy(&data->life.eat),
			pthread_mutex_destroy(&data->life.time),
			msg("Error in mutex init\n"), 4);
	return (1);
}

int	init(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[0]);
	data->life.time_death = ft_atoi(argv[1]);
	data->life.time_eat = ft_atoi(argv[2]);
	data->life.time_sleep = ft_atoi(argv[3]);
	if (argv[4])
		data->life.need_eating = ft_atoi(argv[4]);
	else
		data->life.need_eating = 0;
	data->life.smbdy_died = 0;
	data->life.start = 0;
	init_mutex(data);
	if (!make_philo(data))
		return (msg("Malloc error from mutex"), 0);
	return (1);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->life.write);
	pthread_mutex_destroy(&data->life.eat);
	pthread_mutex_destroy(&data->life.time);
	pthread_mutex_destroy(&data->life.dead);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(data->philos[i].right_fork);
		free(data->philos[i].right_fork);
		i++;
	}
}
