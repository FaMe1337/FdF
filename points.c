/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:01:16 by famendes          #+#    #+#             */
/*   Updated: 2024/09/11 18:03:42 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	three_d_point(t_data *data) //memoria allocada para initial_points
{
	int	i;
	int x;
	int	y;

	i = 0;
	data->initial_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_ipoint));
	if (!data->initial_points)
		error("Malloc for 3D points failed");
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
}

void	two_d_point(t_data *data) //memoria allocada para final_points
{
	int i;

	i = 0;
	float angle = (30 * M_PI/180);
	data->final_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_fpoint));
	if (!data->final_points)
		error("Malloc for 2d points failed");
	while (i < data->map_hcount * data->map_wcount)
	{
		data->final_points[i].x = (data->initial_points[i].x * cos(angle) + data->initial_points[i].y * cos(angle + 2) + data->initial_points[i].z * cos(angle - 2));
		data->final_points[i].y = (data->initial_points[i].x * sin(angle) + data->initial_points[i].y * sin(angle + 2) + data->initial_points[i].z * sin(angle - 2));
		data->final_points[i].x *= 25;
		data->final_points[i].y *= 25;
		i++;
	}
	get_max_and_min(data);
	centralize_points(data);
}

void	get_max_and_min(t_data *data)
{
	int	i;

	i = 0;
	data->max_x = data->final_points[i].x;
	data->min_x = data->final_points[i].x;
	data->max_y = data->final_points[i].y;
	data->min_y = data->final_points[i].y;
	while (i + 1 < data->map_hcount * data->map_wcount)
	{
		if (data->final_points[i].x < data->final_points[i + 1].x)
			data->max_x = data->final_points[i + 1].x;
		if (data->final_points[i].x > data->final_points[i + 1].x)
			data->min_x = data->final_points[i + 1].x;
		if (data->final_points[i].y < data->final_points[i + 1].y)
			data->max_y = data->final_points[i + 1].y;
		if (data->final_points[i].y > data->final_points[i + 1].y)
			data->min_y = data->final_points[i + 1].y;
		i++;
	}
}

void	centralize_points(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_hcount * data->map_wcount)
	{
		data->final_points[i].x += (WINDOW_WIDTH / 1.75)
			- (data->max_x - data->min_x) / 2;
		data->final_points[i].y += (WINDOW_HEIGHT / 2.5)
			- (data->max_y - data->min_y) / 2;
		i++;
	}
}
