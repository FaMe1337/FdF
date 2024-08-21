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

//mouse press em standyimg.img = mlx_new_image(img.mlx, 1200, 1000);
/* int	mouse_press(int button, int x, int y, void *param)
{img.img = mlx_new_image(img.mlx, 1200, 1000);
	t_data	*img;

	(void)x;
	(void)y;
	img = (t_data *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, img);
	else if (button == MOUSE_LEFT_BUTTON)
		img->mouse->is_pressed = true;
	return (0);
} */

