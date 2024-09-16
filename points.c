/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   B[1]: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:41:02 b[1] famendes          #+#    #+#             */
/*   Updated: 2024/09/12 22:56:44 b[1] famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	three_d_point(t_data *data) //memoria allocada para ipoints
{
	int x;
	int	y;

	data->ipoints = malloc(data->map_hcount * sizeof(t_ipoint *));
	if (!data->ipoints)
		error("Malloc for 3D points failed");
	y = 0;
	while (y < data->map_hcount)
	{
		data->ipoints[y] = malloc(data->map_wcount * sizeof(t_ipoint));
		x = 0;
		while (x < data->map_wcount)
		{
			data->ipoints[y][x] = (t_ipoint){x, y, data->map[y][x]};
			x++;
		}
		y++;
	}
}

void	two_d_point(t_data *data) //memoria allocada para fpoints
{
	int i;
	int j;
	float angle;

	j = 0;
	angle = (30 * M_PI/180);
	data->fpoints = malloc(data->map_hcount * sizeof(t_fpoint *));
	if (!data->fpoints)
		error("Malloc for 2d points failed");
	while (j < data->map_hcount)
	{
		data->fpoints[j] = malloc(data->map_wcount * sizeof(t_fpoint));
		i = 0;
		while (i < data->map_wcount)
		{
			data->fpoints[j][i].x = (data->ipoints[j][i].x - data->ipoints[j][i].y) * cos(angle);
			data->fpoints[j][i].y = (data->ipoints[j][i].x + data->ipoints[j][i].y) * sin(angle) - (data->ipoints[j][i].z);
			data->fpoints[j][i].x *= 2;
			data->fpoints[j][i].y *= 2;
			i++;
		}
		j++;
	}
 	get_max_and_min(data);
	centralize_points(data);
}

void	get_max_and_min(t_data *data)
{
	int	i;
	int j;

	j = 0;
	data->max_x = data->fpoints[j][0].x;
	data->min_x = data->fpoints[j][0].x;
	data->max_y = data->fpoints[j][0].y;
	data->min_y = data->fpoints[j][0].y;
	while (j < data->map_hcount)
	{
		i = 0;
		while (i + 1 < data->map_wcount)
		{
			if (data->fpoints[j][i].x < data->fpoints[j][i + 1].x)
				data->max_x = data->fpoints[j][i + 1].x;
			if (data->fpoints[j][i].x > data->fpoints[j][i + 1].x)
				data->min_x = data->fpoints[j][i + 1].x;
			if (data->fpoints[j][i].y < data->fpoints[j][i + 1].y)
				data->max_y = data->fpoints[j][i + 1].y;
			if (data->fpoints[j][i].y > data->fpoints[j][i + 1].y)
				data->min_y = data->fpoints[j][i + 1].y;
			i++;
		}
		j++;
	}
}

void	centralize_points(t_data *data)
{
	int	i;
	int j;

	j = 0;
	while (j < data->map_hcount)
	{
		i = 0;
		while (i < data->map_wcount)
		{
			data->fpoints[j][i].x += (WINDOW_WIDTH / 2)
			- (data->max_x - data->min_x) / 2;
			data->fpoints[j][i].y += (WINDOW_HEIGHT / 2)
			- (data->max_y - data->min_y) / 2;
			i++;
		}
		j++;
	}
}
