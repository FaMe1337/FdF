#include "fdf.h"

//esc bottom
int	close_window(int keysim, t_data *data)
{
	if (keysim == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	printf ("the %d key has been pressed\n", keysim);
	return 0;
}
