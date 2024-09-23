/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:01:16 by famendes          #+#    #+#             */
/*   Updated: 2024/09/20 14:08:15 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_points(t_data *data, char **tab, int y)
{
	int		x;
	int		i;
	char	**z_and_color;

	x = 0;
	while (tab[x] && *tab[x] != '\n')
	{
		z_and_color = ft_split(tab[x], ',');
		data->ipoints[y][x].x = x;
		data->ipoints[y][x].y = y;
		data->ipoints[y][x].z = ft_atoi(z_and_color[0]);
		if (z_and_color[1])
			data->ipoints[y][x].z_color = ft_atoi_base(z_and_color[1], 16);
		else
			data->ipoints[y][x].z_color = 0x4b0082;
		i = 0;
		while (z_and_color[i])
			free(z_and_color[i++]);
		free(z_and_color);
		x++;
	}
	x = 0;
	while (tab[x])
		free(tab[x++]);
	free(tab);
}

void	two_d_point(t_data *data)
{
	int		j;
	float	angle;

	angle = (data->angle * M_PI / 180);
	j = 0;
	data->fpoints = malloc(data->map_hcount * sizeof(t_fpoint *));
	if (!data->fpoints)
		error("Malloc for 2d rows points failed");
	while (j < data->map_hcount)
	{
		data->fpoints[j] = malloc(data->map_wcount * sizeof(t_fpoint));
		if (!data->fpoints)
			error("Malloc for 2d collums points failed");
		points_to_struct(data, j, angle);
		j++;
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
					- (data->max_x - data->min_x) / 2) + data->move_x;
			data->fpoints[j][i].y += ((WINDOW_HEIGHT / 2)
					- (data->max_y - data->min_y) / 2) + data->move_y;
			i++;
		}
		j++;
	}
}

int	get_zoom(t_data *data)
{
	data->zoom = ft_min(WINDOW_WIDTH / data->map_wcount / 2,
			WINDOW_HEIGHT / data->map_hcount / 2);
	return (data->zoom);
}
