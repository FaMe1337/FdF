/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:32:28 by famendes          #+#    #+#             */
/*   Updated: 2024/09/18 17:44:00 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

void	clean_maps(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_hcount)
		free(data->map[y++]);
	free(data->map);
	y = 0;
	while (y < data->map_hcount)
		free(data->ipoints[y++]);
	free(data->ipoints);
	y = 0;
	while (y < data->map_hcount)
		free(data->fpoints[y++]);
	free(data->fpoints);
}

float	calculate_factor(t_data *data)
{
	int	z_range;

	z_range = data->max_z - data->min_z;
	if (z_range >= 10)
		return (0.1);
	if (z_range >= 100)
		return (0.01);
	if (z_range >= 1000)
		return (0.001);
	else
		return (0.9);
}

void	get_max_and_min(t_data *data)
{
	int	i;
	int	j;

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
