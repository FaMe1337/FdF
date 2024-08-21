/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:52:49 by famendes          #+#    #+#             */
/*   Updated: 2024/08/21 19:09:24 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_data data;
	int x;
	int y = 0;

	data.map_path = av[1];
	data.map_hcount = 0;
	data.map_wcount = 0;
	data.y = 0;
	if (ac == 2)
	{
		check_extension(&data);
		get_map_size(&data);
		check_map_is_square(&data);
		copy_map(&data);
	}
	else 
		error("Wrong number of arguments");
	printf("wcount %i\n", data.map_wcount);
	printf("hcount %i\n", data.map_hcount);
	while(y < data.map_hcount)
	{
		x = 0;
		while(x < data.map_wcount)
			printf("%i ", data.map[y][x++]);
		printf("\n");
		y++;
	}
	printf("y %i\n", y);
	printf("x %i\n", x);
	return (0);
}


int	error(char *error_message)
{
	ft_printf("%s\n", error_message);
	exit (1);
}