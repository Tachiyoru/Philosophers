/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:40:23 by sleon             #+#    #+#             */
/*   Updated: 2023/02/06 11:43:51 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init(t_data *data, char **argv)
{
	int	i;

	i = -1;
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
	semaphore_init(data);
	while (++i < data->nbr_philo)
	{
		data->philos[i].life = &data->life;
		data->philos[i].dying = 0;
		data->philos[i].nbr = i + 1;
		data->philos[i].has_eaten = 0;
	}
	return (1);
}

int	semaphore_init(t_data *data)
{
	sem_unlink("forks");
	data->life.fork = sem_open("forks", O_CREAT, 0644, data->nbr_philo);
	if (data->life.fork == SEM_FAILED)
		return (msg("Error sem_open\n"), 0);
	sem_unlink("eat");
	data->life.eat = sem_open("eat", O_CREAT, 0644, 1);
	if (data->life.eat == SEM_FAILED)
		return (msg("Error sem_open\n"), 0);
	sem_unlink("time");
	data->life.time = sem_open("time", O_CREAT, 0644, 1);
	if (data->life.time == SEM_FAILED)
		return (sem_close(data->life.fork), msg("Error sem_open\n"), 0);
	sem_unlink("writer");
	data->life.write = sem_open("writer", O_CREAT, 0644, 1);
	if (data->life.write == SEM_FAILED)
		return (sem_close(data->life.fork), msg("Error sem_open\n"), 0);
	sem_unlink("dead");
	data->life.dead = sem_open("dead", O_CREAT, 0644, 1);
	if (data->life.dead == SEM_FAILED)
		return (sem_close(data->life.fork), msg("Error sem_open\n"), 0);
	return (1);
}
