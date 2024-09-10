/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:41:02 by famendes          #+#    #+#             */
/*   Updated: 2024/09/10 11:15:39 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	i = 0;
	//clean_map(data);
}



void	two_d_point(t_data *data) //memoria allocada para final_points
{
	int i;

	i = 0;
	data->final_points = malloc(data->map_hcount * data->map_wcount * sizeof(t_fpoint));
	if (!data->final_points)
		error("Malloc for 2d points failed", data);
	while (i < data->map_hcount * data->map_wcount)
	{
		/* data->final_points[i].x = WINDOW_WIDTH  / 2 + 40 * (data->initial_points[i].x * cos(120) + data->initial_points[i].y * cos(120 + 2) + data->initial_points[i].z  * cos(120 - 2));
		data->final_points[i].y = WINDOW_HEIGHT / 4  + 40 * (data->initial_points[i].x * sin(120) + data->initial_points[i].y * sin(120 + 2) + data->initial_points[i].z * sin(120 - 2)); */
		data->final_points[i].x = (data->initial_points[i].x - data->initial_points[i].y) * cos(0.663599);
		data->final_points[i].y = (data->initial_points[i].x + data->initial_points[i].y) * sin(0.663599) - data->initial_points[i].z;
		i++;
	}
	i = 0;
	while (i < data->map_hcount * data->map_wcount){
		printf("o x é: %d, o y é: %d\n", data->final_points[i].x, data->final_points[i].y);
		i++;
	}
}

/* void draw_line(t_data data, t_fpoint point0, t_fpoint point1)//point0 = 1 point1 = i *+ 1
{

} */
