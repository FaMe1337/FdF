/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:55:09 by famendes          #+#    #+#             */
/*   Updated: 2024/09/20 01:21:02 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


// é aqui que vou dizer o que faz cada tecla
int		key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	if (keycode == XK_Up)
		data->move_y -= 10;
	if (keycode == XK_Down)
		data->move_y += 10;
	if (keycode == XK_Left)
		data->move_x -= 10;
	if (keycode == XK_Right)
		data->move_x += 10;
	if (keycode == XK_KP_Add)
		data->zoom /= 0.90;
	if (keycode == XK_KP_Subtract)
		data->zoom *= 0.90;
	if (keycode == XK_equal)
		data->angle += 10;
	if (keycode == XK_minus)
		data->angle -= 10;
	if (keycode == XK_p)
		data->z_scale /= 0.9;
	if (keycode == XK_m)
		data->z_scale *= 0.9;
	render(data);
	return (0);
}
//esc bottom
int		close_window(t_data *data)
{
		clean_maps(data);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
}

void	render(t_data *data)
{
	int	y;

	y = 0;
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed");
	while (y < data->map_hcount)
		free(data->fpoints[y++]);
	free(data->fpoints);
	draw(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
