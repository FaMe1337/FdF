/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:01:16 by famendes          #+#    #+#             */
/*   Updated: 2024/09/10 18:51:18 by famendes         ###   ########.fr       */
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
}


void	two_d_point(t_data *data) //memoria allocada para final_points
{
	int i;

	i = 0;
	float angle = 7.37;
	data->final_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_fpoint));
	if (!data->final_points)
		error("Malloc for 2d points failed", data);
	while (i < data->map_hcount * data->map_wcount)
	{
		/* data->final_points[i].x = WINDOW_WIDTH  / 2 + 40 * (data->initial_points[i].x * cos(120) + data->initial_points[i].y * cos(120 + 2) + data->initial_points[i].z  * cos(120 - 2));
		data->final_points[i].y = WINDOW_HEIGHT / 4  + 40 * (data->initial_points[i].x * sin(120) + data->initial_points[i].y * sin(120 + 2) + data->initial_points[i].z * sin(120 - 2)); */
		data->final_points[i].x = WINDOW_WIDTH / 2 + 25 * (data->initial_points[i].x - data->initial_points[i].z); //* 0.866);
		data->final_points[i].y = WINDOW_HEIGHT / 2 + 25 * (data->initial_points[i].y + (data->initial_points[i].x + data->initial_points[i].z)); //* 0.5));
		i++;
	}
	i = 0;
	while (i < data->map_hcount * data->map_wcount){
		printf("o x é: %d, o y é: %d\n", data->final_points[i].x, data->final_points[i].y);
		i++;
	}
}
