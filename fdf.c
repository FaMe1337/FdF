/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:10:35 by famendes          #+#    #+#             */
/*   Updated: 2024/06/28 17:03:11 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data	img;
	

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1200, 1000, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1200, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
 	my_mlx_pixel_put(&img, 5, 5, 0xFFFFFFF);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
/* 	mlx_hook(img.mlx_win, 4, 0, mouse_press, &img); */
	mlx_hook(img.mlx_win, KeyPress, KeyPressMask, close_window, &img);
	mlx_loop(img.mlx);
}
