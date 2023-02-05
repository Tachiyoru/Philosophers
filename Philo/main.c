/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:45:08 by sleon             #+#    #+#             */
/*   Updated: 2023/02/02 17:04:53 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_write_status(t_philos *philo1, char *action, char *color)
{
	long long	time;

	time = get_time_since_start(philo1->life->start);
	if (any_dead(philo1))
		return (1);
	pthread_mutex_lock(&philo1->life->write);
	printf("%s%lli\t%d %s"NC, color, time, philo1->nbr, action);
	pthread_mutex_unlock(&philo1->life->write);
	return (0);
}

int	only_numbers(char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc - 1)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("number_of_philo time_to_die time_to_eat \
time_to_sleep [number_eat].\n");
		return (0);
	}
	if (ft_atoi(argv[0]) <= 0 || ft_atoi(argv[0]) > 200)
		return (msg("Nbr of philo must be between 1 and 200\n"), 0);
	i = 0;
	if (only_numbers(argv, argc))
		return (msg("Args must be numbers\n"), 0);
	while (argv[++i])
		if (ft_atoi(argv[i]) <= 0)
			return (msg("Incorrect argument \n"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, ++argv))
		return (1);
	if (ft_atoi(argv[0]) == 1)
		return (solitary(argv), 0);
	if (!init(&data, argv))
		return (3);
	if (!make_thread(&data))
		return (4);
	destroy_all(&data);
}
