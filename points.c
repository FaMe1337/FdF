/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:01:16 by famendes          #+#    #+#             */
/*   Updated: 2024/09/18 18:22:52 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	three_d_point(t_data *data)
{
	int	x;
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
	data->z_scale = get_z_scale(data);
}

void	two_d_point(t_data *data)
{
	int		i;
	int		j;
	float	angle;

	angle = 30 * M_PI / 180;
	j = -1;
	data->fpoints = malloc(data->map_hcount * sizeof(t_fpoint *));
	if (!data->fpoints)
		error("Malloc for 2d rows points failed");
	while (++j < data->map_hcount)
	{
		data->fpoints[j] = malloc(data->map_wcount * sizeof(t_fpoint));
		if (!data->fpoints)
			error("Malloc for 2d collums points failed");
		i = -1;
		while (++i < data->map_wcount)
		{
			data->fpoints[j][i].x = ((data->ipoints[j][i].x
						- data->ipoints[j][i].y) * cos(angle)) * get_zoom(data);
			data->fpoints[j][i].y = ((data->ipoints[j][i].x
						+ data->ipoints[j][i].y) * sin(angle)
					- (data->ipoints[j][i].z * data->z_scale)) * get_zoom(data);
		}
	}
	centralize_points(data);
}

float	get_z_scale(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->max_z = data->ipoints[y][0].z;
	data->min_z = data->ipoints[y][0].z;
	while (y < data->map_hcount)
	{
		x = 0;
		while (x < data->map_wcount)
		{
			if (data->ipoints[y][x].z > data->max_z)
				data->max_z = data->ipoints[y][x].z;
			if (data->ipoints[y][x].z < data->min_z)
				data->min_z = data->ipoints[y][x].z;
			x++;
		}
		y++;
	}
	return (calculate_factor(data));
}

void	centralize_points(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	get_max_and_min(data);
	while (j < data->map_hcount)
	{
		i = 0;
		while (i < data->map_wcount)
		{
			data->fpoints[j][i].x += ((WINDOW_WIDTH / 2)
				- (data->max_x - data->min_x) / 2) + data->move_x; // + data->pos_w
			data->fpoints[j][i].y += ((WINDOW_HEIGHT / 2)
				- (data->max_y - data->min_y) / 2) + data->move_y; // +  data->pos_h;
			i++;
		}
		j++;
	}
	printf("o x e: %d\n", data->move_x);
}

int	get_zoom(t_data *data)
{
	data->zoom = ft_min(WINDOW_WIDTH / data->map_wcount / 2,
			WINDOW_HEIGHT / data->map_hcount / 2);
	return (data->zoom);
}
