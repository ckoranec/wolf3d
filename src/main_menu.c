#include "wolf.h"

void                select_button(t_mlx *mlx)
{
	t_button *b = mlx->mode->button;
	int i;
	for (i = 0; i < mlx->mode->button_count; i++)
	{
		if (b[i].selected)
			break ;
	}
	if (i >= mlx->mode->button_count)
		return ;
	if (b[i].selected && !ft_strcmp(b[i].label, "exit"))
		mlxdel(mlx);
	else if (b[i].selected && !ft_strcmp(b[i].label, "continue"))
		remove_mode(mlx);
}

int					menu_mode(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		remove_mode(mlx);
	else if (key == KEY_UP)
		cycle_button('U', mlx);
	else if (key == KEY_DOWN)
		cycle_button('D', mlx);
	if (key == KEY_ENTER)
		select_button(mlx);
	return (0);
}

void		draw_menu(t_mlx *mlx, t_input_stack *in)
{
	for(int y = in->y; y < in->y + in->size_y; y++)
	{
		for(int x = in->x; x < in->x + in->size_x; x++)
		{
			image_set_pixel(mlx->image, x, y, MAROON);
		}
	}
	for (int b = 0; b < in->button_count; b++)
		print_button(&in->button[b], mlx);
}

void		init_menu(t_input_stack *mode)
{
	mode->draw = draw_menu;
	mode->handler = menu_mode;
	mode->button = ft_memalloc(sizeof(t_button) * 2);
	mode->button_count = 2;
	mode->size_x = 200;
	mode->size_y = 500;
	mode->x = (WIN_WIDTH / 2) - (mode->size_x / 2);
	mode->y = (WIN_HEIGHT / 2) - (mode->size_y / 2);
	t_vect_2 button_size = { 180, 20 };
	push_button(&mode->button[0], "continue",
		(t_vect_2){ mode->x + 10, mode->y + 10 }, button_size, GREEN);
	push_button(&mode->button[1], "exit",
		(t_vect_2){ mode->x + 10, mode->y + 40 }, button_size, GREEN);
	mode->button[0].selected = true;
}
