/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:41:02 by famendes          #+#    #+#             */
/*   Updated: 2024/09/04 12:28:25 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	three_d_point(t_data *data)
{
	int	i;
	int x;
	int	y;

	i = 0;
	data->initial_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_ipoint));
	if (!data->initial_points)
		error("Malloc for 3D points failed", data);
	y = 0;
	while (y < data->map_hcount)
	{
		x = 0;
		while (x < data->map_wcount)
		{
			data->initial_points[i] = (t_ipoint){x, y, data->map[y][x]};
			i++;
			x++;
		}
		y++;
	}
		while (i < data->map_hcount * data->map_wcount)
	{
		printf("no ponto[%d] x é: %d, y é: %d e no ponto z é: %d\n", i, data->initial_points[i].x, data->initial_points[i].y, data->initial_points[i].z);
		i++;
	}
	//clean_map(data);
}



void	two_d_point(t_data *data)
{
	int i;

	i = 0;
	data->final_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_fpoint));
	if (!data->final_points)
		error("Malloc for 2d points failed", data);
	while (i < data->map_hcount * data->map_wcount)
	{
		data->final_points[i].y = data->initial_points[i].x * sin(35.26 * (M_PI / 180.0)) + data->initial_points[i].y * sin(35.26 * (M_PI / 180.0)) - data->initial_points[i].z * cos(35.26 * (M_PI / 180.0));
		data->final_points[i].x = data->initial_points[i].x * cos(45 * (M_PI / 180.0)) - data->initial_points[i].y * cos(45 * (M_PI / 180.0));
		i++;
		/* data->final_points[i].x = data->initial_points[i].x * cos(120) + data->initial_points[i].y * cos(120 + 2) + data->initial_points[i].z  * cos(120 - 2);
		data->final_points[i].y = data->initial_points[i].x * sin(120) + data->initial_points[i].y * sin(120 + 2) - data->initial_points[i].z * sin(120 - 2); */
	}
	i = 0;
	while (i < data->map_hcount * data->map_wcount)
	{
		printf("no ponto[%d] x é: %d, y é: %d\n", i, data->final_points[i].x, data->final_points[i].y);
		i++;
	}
}

void	draw_line(t_data *data, t_fpoint point0, t_fpoint point1)
{
	float	step;
	float	x;
	float	y;
	int		i;
	t_delta	delta;

	i = 0;
	delta.dx = point1.x - point0.x;
	delta.dy = point1.y - point0.y;
	if (fabsf(delta.dx) >= fabsf(delta.dy))
		step = fabsf(delta.dx);
	else
		step = fabsf(delta.dy);
	delta.dx = delta.dx / step;
	delta.dy = delta.dy / step;
	x = point0.x;
	y = point0.y;
	while (i < step)
	{
		my_mlx_pixel_put(data, -x + WINDOW_WIDTH / 2 , -y + WINDOW_HEIGHT / 2 , 0xffffff);
		x = x + delta.dx;
		y = y + delta.dy;
		i++;
	}
}
