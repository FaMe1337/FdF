/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:14:18 by famendes          #+#    #+#             */
/*   Updated: 2024/09/16 12:31:15 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw(t_data *data)
{
    int x;
    int y;

    y = 0;
 	while (y < data->map_hcount)
	{
		x = 0;
		while (x < data->map_wcount)
		{
			if (x != data->map_wcount - 1)
				bresenham(&data->fpoints[y][x], &data->fpoints[y][x + 1], data);
			if (y != data->map_hcount - 1)
				bresenham(&data->fpoints[y][x], &data->fpoints[y + 1][x], data);
			x++;
		}
		y++;
	}
}

		//t_points sao floats
void	bresenham(t_fpoint *p0, t_fpoint *p1, t_data *data)
{
	int			sx;
	int			sy;
	t_bresenham	points;

	sort_struc(p0, p1, &points);
	sx = find_s(p0->x, p1->x);
	sy = find_s(p0->y, p1->y);
 	while ((int)points.x0 != (int)p1->x && (int)points.y0 != (int)p1->y)
	{
		my_mlx_pixel_put(data, points.x0, points.y0, 0xFFFFFF);
		points.max = 2 * points.error;
		if (points.max > -points.y_step)
		{
			points.error -= points.y_step;
			points.x0 += sx;
		}
		if (points.max < points.x_step)
		{
			points.error += points.x_step;
			points.y0 += sy;
		}
	}
}

void	sort_struc(t_fpoint *p0, t_fpoint *p1, t_bresenham *points)
{
    points->x0 = p0->x;
    points->y0 = p0->y;
    points->x_step = fabs(p1->x - p0->x);
    points->y_step = fabs(p1->y - p0->y);
    points->error = points->x_step - points->y_step;
    points->max = 2 * points->error;
}

int find_s(float x, float x1)
{
	if (x < x1)
		return (1);
	return (-1);
}
