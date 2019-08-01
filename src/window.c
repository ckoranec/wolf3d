/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:56:37 by calamber          #+#    #+#             */
/*   Updated: 2019/08/01 00:09:48 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		cam_reset(t_mlx *mlx)
{
	mlx->cam->x = 0;
	mlx->cam->y = 0;
}

void		mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	exit(0);
}

int			newwindow(t_mlx *s, char *title)
{
	ft_memset(s, 0, sizeof(t_mlx));
	if (!(s->mlx = mlx_init()) ||
		!(s->window = mlx_new_window(s->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
	{
		free(title);
		if (s->window)
			mlx_destroy_window(s->mlx, s->window);
		return (1);
	}
	free(title);
	return (0);
}

int			init(char *title, t_mlx *mlx)
{
	if (newwindow(mlx, title) || (mlx->cam = ft_memalloc(sizeof(t_cam)))
		== NULL || (mlx->image = new_image(mlx)) == NULL)
		mlxdel(mlx);
	mlx->cam->x = 0;
	mlx->cam->y = 0;
	return (1);
}
