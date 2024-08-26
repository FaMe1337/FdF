/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:10:35 by famendes          #+#    #+#             */
/*   Updated: 2024/08/23 19:03:23 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mlx_display(t_data *data)
{
	//creating win
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Mlx connection failed", data);
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, data->map_path);
	if (!data->mlx_win)
		error("Mlx win creation failed", data);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed", data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	//putting pixels in win
	for (int y = WINDOW_HEIGHT * 0.1; y < WINDOW_HEIGHT * 0.9; y++)
	{
		for (int x = WINDOW_HEIGHT * 0.1; x < WINDOW_WIDTH * 0.9; x++)
			my_mlx_pixel_put(data, x, y, 0xFFFFFF);
	}
	//mlx_hook(img.mlx_win, 4, 0, mouse_press, &img);
	mlx_key_hook(data->mlx_win, f, &data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, close_window, &data);
	mlx_loop(data->mlx);
}
