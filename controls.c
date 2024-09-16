/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:31:11 by famendes          #+#    #+#             */
/*   Updated: 2024/09/16 12:46:02 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// é aqui que vou dizer o que faz cada tecla
int		key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
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

