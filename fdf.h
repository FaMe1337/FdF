/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:23:48 by famendes          #+#    #+#             */
/*   Updated: 2024/08/21 18:47:44 by famendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx/mlx.h"
# include "Libft/libft.h"
# include "printf/ft_printf.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* typedef struct			s_camera
{
	t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					x_offset;
	int					y_offset;
}						t_camera;
 */
typedef struct	s_data {
	void	*img;
	void	*mlx;
	void	*mlx_win;
	char	*addr;
	char	*map_path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		map_wcount;
	int		map_hcount;
	int		**map;
	int		y;
	int		x;
	//t_mouse	*mouse;
	//t_camera	*camera;
}				t_data;

typedef struct			s_mouse
{
	char				is_pressed;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;

//error
int	error(char *message);

// print pixels
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//controls ui
/* int		mouse_press(int button, int x, int y, void *param); */
int		close_window(int keysim, t_data *data);

//map info
int		check_extension(t_data *data);
void	copy_map(t_data *data);
void	get_map_size(t_data *data);
void	check_map_is_square(t_data *data);

#endif