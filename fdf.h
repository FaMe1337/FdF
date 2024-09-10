/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:33:49 by famendes          #+#    #+#             */
/*   Updated: 2024/09/10 11:33:51 by famendes         ###   ########.fr       */
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

typedef struct s_ipoint{
	int	x;
	int y;
	int z;
}				t_ipoint;

typedef struct s_fpoint{
	int	x;
	int y;
}				t_fpoint;

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
	//t_mouse	*mouse;
	t_ipoint	*initial_points;
	t_fpoint	*final_points;
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
void	error(char *message, t_data *data);

//point conversion
void	three_d_point(t_data *data);
void	two_d_point(t_data *data);

// mlx related
void	mlx_display(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *data, t_fpoint point0, t_fpoint point1);

//controls ui
/* int		mouse_press(int button, int x, int y, void *param); */
int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);

//map info
void 	clean_and_copy(t_data *data, char **tab, int y);
void	check_extension(t_data *data);
void	copy_map(t_data *data);
void	get_map_size(t_data *data);
void	check_map_is_square(t_data *data);
void	clean_map(t_data *data);

#endif
