#include "wolf.h"


void				push_mode_stack(void (*handler)(t_input_stack *mode), t_mlx *mlx)
{
	t_input_stack *new;

	printf("pushing mode to stack\n");
	new = ft_memalloc(sizeof(t_input_stack));
	new->prev = NULL;
	new->next = mlx->mode;
	if (mlx->mode)
		mlx->mode->prev = new;
	new->x = mlx->mode ? mlx->mode->x + 50 : 0;
	new->y = mlx->mode ? mlx->mode->y + 50 : 0;
	handler(new);
	mlx->mode = new;
}

void				remove_mode(t_mlx *mlx)
{
	printf("removing layer");
	t_input_stack *tmp;
	bool			last = false;
	//if (!mlx->mode)
	//	return ;
	tmp = mlx->mode;
	mlx->mode = mlx->mode->next;
	last = tmp == mlx->mode ? true : false;
    if (tmp->button)
    {
        free(tmp->button);
    }
    free(tmp);
	tmp = NULL;
	if (last)
		mlx->mode = NULL;
	else
		mlx->mode->prev = NULL;
}

void                print_button(t_button *arr, t_mlx *mlx)
{
    for (int y = arr->origin.y; y < arr->origin.y + arr->size.y; y++)
    {
        for (int x = arr->origin.x; x < arr->origin.x + arr->size.x; x++)
            image_set_pixel(mlx->image, x, y, arr->selected ? WHITE : arr->color);
    }
    mlx_string_put(mlx->mlx, mlx->window, arr->origin.x + (arr->size.x / 2),
        arr->origin.y + (arr->size.y / 2), BLACK, arr->label);
}

void				cycle_button(char t, t_mlx *mlx)
{
	t_button *arr;
	int i = 0;

	arr = mlx->mode->button;
	if (!arr)
		return ;
	while (i < mlx->mode->button_count)
	{
		if (arr[i].selected)
			break ;
		i++;
	}
	arr[i].selected = false;
	if (t == 'U')
		i = (i == 0 ? mlx->mode->button_count : i) - 1;
	if (t == 'D')
		i = i == mlx->mode->button_count - 1 ? 0 : i + 1;
	arr[i].selected = true;
}

void				push_button(t_button *new, char *label, t_vect_2 origin, t_vect_2 size, int color)
{
	printf("pushing button to stack\n");
	new->label = label;
	new->color = color;
	new->selected = false;
	new->origin = origin;
	new->size = size;
}
