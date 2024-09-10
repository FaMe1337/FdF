/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:10:35 by famendes          #+#    #+#             */
/*   Updated: 2024/09/09 14:32:31 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	mlx_display(t_data *data)
{
	//creating win
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Mlx connection failed", data);
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, data->map_path);
	if (!data->mlx_win)
		error("Mlx window creation failed", data);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed", data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	//putting pixels in win
	three_d_point(data); //memoria alocada para initial points
	two_d_point(data); //memoria alocada para final points
	//hooks
 	int i = 0;
	while (i < data->map_hcount * data->map_wcount)
	{
		my_mlx_pixel_put(data, data->final_points[i].x, data->final_points[i].y, 0xFFFFFF);
		i++;
	}
	mlx_key_hook(data->mlx_win, key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
