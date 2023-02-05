/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:35:58 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:04:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
