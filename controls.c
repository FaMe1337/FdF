#include "fdf.h"

//esc bottom
int	close_window(int keysim, t_data *count_values)
{
	if (keysim == 0xff1b){
		mlx_destroy_window(count_values->mlx, count_values->mlx_win);
		mlx_destroy_display(count_values->mlx);	
		free(count_values->mlx);
		exit(0);
	}
	return 0;
}

//mouse press em standy
int	mouse_press(int button, int x, int y, void *param)
{
	t_data	*img;

	(void)x;
	(void)y;
	img = (t_data *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, img);
	else if (button == MOUSE_LEFT_BUTTON)
		img->mouse->is_pressed = true;
	return (0);
}
//zoom em standy
void	zoom(int key, t_data *img)
{
	if (key == NUM_PAD_PLUS ||
		key == MAIN_PAD_PLUS ||
		key == MOUSE_SCROLL_UP)
		img->camera->zoom++;
	else if (key == NUM_PAD_MINUS ||
		key == MAIN_PAD_MINUS ||
		key == MOUSE_SCROLL_DOWN)
		img->camera->zoom--;
	if (img->camera->zoom < 1)
		img->camera->zoom = 1;
	draw(img->map, img);
}
