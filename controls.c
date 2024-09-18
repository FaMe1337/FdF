/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:55:09 by famendes          #+#    #+#             */
/*   Updated: 2024/09/18 18:23:46 by famendes         ###   ########.fr       */
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
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error("Mlx img creation failed");
	draw(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
