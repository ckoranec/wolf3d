/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:56:37 by calamber          #+#    #+#             */
/*   Updated: 2019/08/07 18:07:24 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	if (mlx->map.matrix)
		map_destroy(&mlx->map);
	exit(0);
}

int			newwindow(t_mlx *s, char *title)
{
	ft_memset(&s->player, 0, sizeof(t_player));
	if (!(s->mlx = mlx_init()) ||
		!(s->window = mlx_new_window(s->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
	{
		if (s->window)
			mlx_destroy_window(s->mlx, s->window);
		return (1);
	}
	return (0);
}

int			init_it(char *title, t_mlx *mlx)
{
	if (newwindow(mlx, title) || (mlx->image = new_image(mlx)) == NULL)
	{
		mlxdel(mlx);
		return (0);
	}
	return (1);
}
