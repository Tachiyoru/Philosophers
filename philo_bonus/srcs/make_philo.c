/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:44:33 by sleon             #+#    #+#             */
/*   Updated: 2023/02/06 11:45:06 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	make_philo(t_data *data)
{
	int			i;

	i = 0;
	data->life.start = get_time();
	while (i < data->nbr_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (msg("Error fork"), kill_process_until(data, i), 1);
		if (data->pid[i] == 0)
			life(&data->philos[i], data);
		i += 2;
		if (i >= data->nbr_philo && i % 2 == 0)
		{
			i = 1;
			if (data->life.time_eat < data->life.time_death)
				ft_usleep(data, data->life.time_eat);
			else
				ft_usleep(data, data->life.time_death / 2);
		}
	}
	ft_waitpid_kill(data);
	return (0);
}

int	ft_waitpid_kill(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		while (++i < data->nbr_philo)
			kill(data->pid[i], SIGKILL);
		destroy_semaphore(data);
		return (0);
	}
	i = -1;
	while (++i < data->nbr_philo)
		waitpid(data->pid[i], &status, 0);
	destroy_semaphore(data);
	return (0);
}

int	kill_process_until(t_data *data, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		usleep(100);
		kill(data->pid[i], SIGKILL);
		i += 2;
		if (i > until && i % 2 == 0)
			i = 1;
	}
	return (0);
}
