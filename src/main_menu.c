#include "wolf.h"

int					menu_mode(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		remove_mode(mlx);
	return (0);
}

void				draw_menu(t_mlx *mlx, t_input_stack *in)
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
	//mlx_string_put(mlx->mlx, mlx->window, in->x,
	//	in->y + in->size_y / 2, WHITE, "hello");
}

void        init_menu(t_input_stack *mode)
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
        (t_vect_2){ mode->x + 10, mode->y + 10 }, button_size, WHITE);
    push_button(&mode->button[1], "exit",
        (t_vect_2){ mode->x + 10, mode->y + 40 }, button_size, WHITE);
    mode->button[0].selected = true;
}