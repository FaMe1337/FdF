/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:14:22 by famendes          #+#    #+#             */
/*   Updated: 2024/09/10 17:53:14 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	limits(t_data *data)
{
	data->c_y = 1;
	data->i = 0;
	while (data->c_y != data->map_hcount)
	{
		data->c_x = 1;
		while (data->c_x < data->map_wcount)
			no_limit(data);
		if (data->c_x == data->map_wcount)
		{
			low_limit(data);
			data->i++;
		}
		data->c_y++;
	}
	data->c_x = 1;
	if (data->c_y == data->map_hcount)
	{
		while (data->c_x != data->map_wcount)
		{
			right_limit(data);
			data->i++;
		}
	}
}

void	no_limit(t_data *data)
{
	right_limit(data);
	low_limit(data);
	data->i++;
}

void	right_limit(t_data *data)
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	x0 = data->final_points[data->i].x;
	y0 = data->final_points[data->i].y;
	x1 = data->final_points[data->i + 1].x;
	y1 = data->final_points[data->i + 1].y;
	data->c_x++;
	draw_line(data, (t_fpoint){x0, y0}, (t_fpoint){x1, y1});
}

void	low_limit(t_data *data)
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	x0 = data->final_points[data->i].x;
	y0 = data->final_points[data->i].y;
	x1 = data->final_points[data->i + data->map_wcount].x;
	y1 = data->final_points[data->i + data->map_wcount].y;
	draw_line(data, (t_fpoint){x0, y0}, (t_fpoint){x1, y1});
}

void draw_line(t_data *data, t_fpoint point0, t_fpoint point1)
{
    int dx;
	int dy;
	int p;

	dx = point1.x - point0.x;
	dy= point1.y - point0.y;
	p = 2 * dy - dx;
	while(abs(point0.x) < abs(point1.x))
	{
		if(p >= 0)
		{
			my_mlx_pixel_put(data, point0.x, point0.y, 0xFFFFFF);
			p = p + 2 * dy - 2 * dx;
			point0.y++;
		}
		else
		{
			my_mlx_pixel_put(data, point0.x, point0.y, 0xFFFFFF);
			p = p + 2 * dy;
		}
		point0.x++;
	}
}
