/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:02:09 by famendes          #+#    #+#             */
/*   Updated: 2024/09/19 23:24:14 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* typedef struct s_color{
    int r;
    int g;
    int b;
} t_color;

int get_color(t_fpoint *p0, t_fpoint *p1, t_bresenham points)
{
    t_color color0 = { p0->color >> 16, (p0->color >> 8) & 0xFF, p0->color & 0xFF }; // Extract RGB from color
    t_color color1 = { p1->color >> 16, (p1->color >> 8) & 0xFF, p1->color & 0xFF }; // Extract RGB from color
    float total_distance = hypot(p1->x - p0->x, p1->y - p0->y);
    float current_distance = hypot(points.x0 - p0->x, points.y0 - p0->y);

    float factor = current_distance / total_distance;
    t_color result;
    result.r = (int)(color0.r + (color1.r - color0.r) * factor);
    result.g = (int)(color0.g + (color1.g - color0.g) * factor);
    result.b = (int)(color0.b + (color1.b - color0.b) * factor);
    return (result.r << 16) | (result.g << 8) | result.b;
} */
//                   começo       final        onde está
int	get_color(t_fpoint *p0, t_fpoint *p1, t_bresenham *bresenham)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (bresenham->color == p1->color)
		return (bresenham->color);
	if (bresenham->x_step > bresenham->y_step)
		percentage = percent(p0->x, p1->x, bresenham->x0);
	else
		percentage = percent(p0->y, p1->y, bresenham->y0);
	red = get_light((p0->color >> 16) & 0xFF,
					(p1->color >> 16) & 0xFF,
					percentage);
	green = get_light((p0->color >> 8) & 0xFF,
					(p1->color >> 8) & 0xFF,
					percentage);
	blue = get_light(p0->color & 0xFF,
					p1->color & 0xFF,
					percentage);
	return ((red << 16) | (green << 8) | blue);
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return(placement / distance);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}