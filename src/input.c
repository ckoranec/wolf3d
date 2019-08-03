/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/08/03 01:27:42 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			rotate_player(bool left, t_mlx *mlx)
{
	t_player *player;

	player = &mlx->player;
	if (left)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(/* rotspeed */0.5f) - player->dir_y * sin(/* rotspeed*/0.5f);
		player->dir_y = oldDirX * sin(0.5f) + player->dir_y * cos(0.5f);
		double oldPlaneX = player->camplane_x;
		player->camplane_x = player->camplane_x * cos(0.5f) - player->camplane_y * sin(0.5f);
		player->camplane_y = oldPlaneX * sin(0.5f) + player->camplane_y * cos(0.5f);
	}
}

static int			fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		mlxdel(mlx);
	if (key == KEY_W)
		;
	if (key == KEY_S)
		;
	if (key == KEY_A)
		rotate_player(true, mlx);
	if (key == KEY_D)
		;
	mlx_draw(mlx);
	return (0);
}

void				start(t_mlx *mlx)
{
	mlx->player.camplane_x = 0;
	mlx->player.camplane_y = 0.66;
	mlx->player.dir_x = 1;
	mlx->player.dir_y = 0;
	ft_printf("playerx %f player7 %f\n", mlx->player.x, mlx->player.y);
	mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
