/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/08/04 23:03:01 by calamber         ###   ########.fr       */
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
		player->dir_x = player->dir_x * cos(player->rotspeed) - player->dir_y * sin(player->rotspeed);
		player->dir_y = oldDirX * sin(player->rotspeed) + player->dir_y * cos(player->rotspeed);
		double oldPlaneX = player->camplane_x;
		player->camplane_x = player->camplane_x * cos(player->rotspeed) - player->camplane_y * sin(player->rotspeed);
		player->camplane_y = oldPlaneX * sin(player->rotspeed) + player->camplane_y * cos(player->rotspeed);
	}
	if (!left)
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = player->dir_x;
      player->dir_x = player->dir_x * cos(-player->rotspeed) - player->dir_y * sin(-player->rotspeed);
      player->dir_y = oldDirX * sin(-player->rotspeed) + player->dir_y * cos(-player->rotspeed);
      double oldPlaneX = player->camplane_x;
      player->camplane_x = player->camplane_x * cos(-player->rotspeed) - player->camplane_y * sin(-player->rotspeed);
      player->camplane_y = oldPlaneX * sin(-player->rotspeed) + player->camplane_y * cos(-player->rotspeed);
	}
}

static int			fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		mlxdel(mlx);
	if (key == KEY_W)
	{
		mlx->player.x += mlx->player.dir_x * mlx->player.movespeed;
		mlx->player.y += mlx->player.dir_y * mlx->player.movespeed;
	}
	if (key == KEY_S)
	{
		mlx->player.x -= mlx->player.dir_x * mlx->player.movespeed;
		mlx->player.y -= mlx->player.dir_y * mlx->player.movespeed;
	}
	if (key == KEY_A)
		rotate_player(true, mlx);
	if (key == KEY_D)
		rotate_player(false, mlx);
	mlx_draw(mlx);
	return (0);
}

void				start(t_mlx *mlx)
{
	mlx->player.camplane_x = 0;
	mlx->player.camplane_y = 0.66f;
	mlx->player.dir_x = -1.0f;
	mlx->player.dir_y = 0;
	mlx->player.rotspeed = 0.2f;
	mlx->player.movespeed = 1.0f;
	mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
