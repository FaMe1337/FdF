/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:38:19 by famendes          #+#    #+#             */
/*   Updated: 2024/09/20 01:31:17 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	mlx_display(t_data *data)
{
	data->z_scale = get_z_scale(data);
	data->zoom = get_zoom(data);
	data->angle = 30;
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Mlx connection failed");
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, data->map_path);
	if (!data->mlx_win)
		error("Mlx window creation failed");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw(data);
	mlx_key_hook(data->mlx_win, key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
