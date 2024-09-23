/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:02:09 by famendes          #+#    #+#             */
/*   Updated: 2024/09/20 14:10:42 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (placement / distance);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
