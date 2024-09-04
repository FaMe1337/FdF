#include "fdf.h"

//esc bottom
int		close_window(t_data *data)
{
		clean_map(data);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
}

// é aqui que vou dizer o que faz cada tecla
int		key_press(int keycode, t_data *data)
{
	if (keycode = XK_Escape)
		close_window(data);
}
