/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begining.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:10:35 by famendes          #+#    #+#             */
/*   Updated: 2024/08/21 19:10:41 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WIDHT 800
#define HEIGHT 800


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	color_screen(t_data *data, int color)
{
	for (int y = 0; y < 800; ++y)	
	{
		for (int x = 0; x < 800; ++x)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}
int f(int keysym, t_data *data)
{
	if (keysym == XK_r)
	{
		color_screen(data, 0xff0000);
	}
	else if (keysym == XK_g)
	{
		color_screen(data, 0xff00);
	}
	else if (keysym == XK_b)
	{
		color_screen(data, 0xff);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	img;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 800, "FDF");
	img.img = mlx_new_image(img.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	for (int y = HEIGHT * 0.1; y < HEIGHT * 0.9; y++)
	{
		for (int x = WIDHT * 0.1; x < WIDHT * 0.9; x++)
			my_mlx_pixel_put(&img, x, y, rand() * 0xFFFFFF);
	}
	//mlx_hook(img.mlx_win, 4, 0, mouse_press, &img);
	mlx_key_hook(img.mlx_win, f, &img);
	//mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, KeyPress, KeyPressMask, close_window, &img);
	mlx_loop(img.mlx);
}
