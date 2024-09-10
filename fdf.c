/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:52:49 by famendes          #+#    #+#             */
/*   Updated: 2024/09/09 14:31:45 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_data data;

	data.map_path = av[1];
	data.map_hcount = 0;
	data.map_wcount = 0;
	if (ac == 2)
	{
		check_extension(&data);
		get_map_size(&data);
		check_map_is_square(&data);
		copy_map(&data);
		mlx_display(&data);
		mlx_loop(data.mlx);
	}
	else
		error("Wrong number of arguments", &data);
	//limpar mapa se for precisso
}
//print the error msg
void	error(char *error_message, t_data *data)
{
	ft_printf("%s\n", error_message);
	exit (1);
}
void	clean_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_hcount)
			free(data->map[y++]);
	free(data->map);
}
