/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:52:49 by famendes          #+#    #+#             */
/*   Updated: 2024/08/23 19:02:48 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_data data;

	data.map_path = av[1];
	data.map_hcount = 0;
	data.map_wcount = 0;
	data.y = 0;
	data.mlx = NULL;
	data.mlx_win = NULL;
	data.img = NULL;
	data.map = NULL;
	if (ac == 2)
	{
		check_extension(&data);
		get_map_size(&data);
		check_map_is_square(&data);
		copy_map(&data);
		mlx_display(&data);
	}
	else
		error("Wrong number of arguments", &data);
	//limpar mapa se for precisso
}
//print the error msg and clean everything that was allocated and not used
void	error(char *error_message, t_data *data)
{
	if (data->map)
		clean_map(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
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
