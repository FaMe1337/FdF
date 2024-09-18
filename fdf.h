/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famendes <famendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:23:48 by famendes          #+#    #+#             */
/*   Updated: 2024/09/18 18:14:31 by famendes         ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	x_step;
	int	y_step;
	int	error;
	int	max;
}			t_bresenham;

typedef struct s_ipoint
{
	int	x;
	int	y;
	int	z;
}				t_ipoint;

typedef struct s_fpoint
{
	int	x;
	int	y;
}				t_fpoint;

typedef struct s_data
{
	void		*img;
	void		*mlx;
	void		*mlx_win;
	char		*addr;
	char		*map_path;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			map_wcount;
	int			map_hcount;
	int			**map;
	int			max_x;
	int			min_x;
	int			max_y;
	int			min_y;
	int			max_z;
	int			min_z;
	float		z_scale;
	int			zoom;
	int 		move_x;
	int			move_y;
	t_ipoint	**ipoints;
	t_fpoint	**fpoints;
}				t_data;

//error
void	error(char *message);

//point conversion
void	three_d_point(t_data *data);
void	two_d_point(t_data *data);
int		get_zoom(t_data *data);
void	centralize_points(t_data *data);
void	get_max_and_min(t_data *data);
float	calculate_factor(t_data *data);
float	get_z_scale(t_data *data);

// mlx related
void	mlx_display(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//draw shenanigans
void	draw(t_data *data);
void	centralize_points(t_data *data);
void	get_max_and_min(t_data *data);
int		find_s(double x, double x1);
void	bresenham(t_fpoint *p0, t_fpoint *p1, t_data *data);
void	sort_struc(t_fpoint *p0, t_fpoint *p1, t_bresenham *points);
int		ft_min(int a, int b);

//controls ui
int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);
void	render(t_data *data);

//map info
void	clean_and_copy(t_data *data, char **tab, int y);
void	check_extension(t_data *data);
void	copy_map(t_data *data);
void	get_map_size(t_data *data);
void	check_map_is_square(t_data *data);
void	clean_maps(t_data *data);

#endif
