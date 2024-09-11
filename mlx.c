/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:38:19 by famendes          #+#    #+#             */
/*   Updated: 2024/09/11 18:44:25 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		error("Mlx connection failed");
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, data->map_path);
	if (!data->mlx_win)
		error("Mlx window creation failed");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	three_d_point(data); //memoria alocada para initial points
	two_d_point(data); //memoria alocada para final points
	//draw_line(data);
	int i = 0;
	while (i + 1 < data->map_wcount * data->map_hcount)
	{
		draw_line(data, data->final_points[i], data->final_points[i + 1]);
		i++;
	}
	mlx_key_hook(data->mlx_win, key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_window, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	draw_line(t_data *data, t_fpoint point0, t_fpoint point1)
{	
	int		step;
	float	dx = point1.x - point0.x;
	float	dy = point1.y - point0.y;
	float	xin;
	float	yin;
	float	x;
	float	y;

	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	xin = dx / step;
	yin = dy / step;
	x = point0.x;
	y = point0.y;
	int i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0xFFFFFF);
		x += xin;
		y += yin;
	}
}
