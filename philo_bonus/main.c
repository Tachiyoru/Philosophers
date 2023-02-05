/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:35:28 by sleon             #+#    #+#             */
/*   Updated: 2023/02/05 20:05:01 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, ++argv))
		return (1);
	if (ft_atoi(argv[0]) == 1)
		return (solitary(argv), 0);
	if (!init(&data, argv))
		return (2);
	if (!make_philo(&data))
		return (3);
	return (0);
}

void	solitary(char **argv)
{
	pid_t		pid1;
	long long	start;

	pid1 = fork();
	if (pid1 == 0)
	{
		start = get_time();
		printf("0	1%s", TAKEN_FORK);
		usleep(1000 * ft_atoi(argv[1]));
		printf(BRED"%s	1 %s"NC, argv[1], PHILO_DIED);
	}
	waitpid(pid1, NULL, 0);
}
