/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/08/05 03:56:26 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"



static void			rotate_v(double angle, t_vect_3 *v)
{
	double x;
	double c;
	double s;

	x = v->x;
	c = cos(angle);
	s = sin(angle);
	v->x = v->x * c - v->y * s;
	v->y = x * s + v->y * c;
}

static void			rotate_player(double angle, t_mlx *mlx)
{
	rotate_v(angle, &mlx->player.dir);
	rotate_v(angle, &mlx->player.cam);
}

static void			move_player(t_mlx *mlx, double amount)
{
	t_vect_3 new = { mlx->player.x, mlx->player.y, 0 };
	if (new.x < 0.5f || new.x > mlx->map.width - 1.5f || new.y < 0.5f || new.y > mlx->map.height - 1.5f)
		return ;
	mlx->player.x  += amount;
	mlx->player.y += amount;
}

static int			fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		mlxdel(mlx);
	if (key == KEY_W)
		move_player(mlx, mlx->player.dir.x * mlx->player.movespeed);
	if (key == KEY_S)
		move_player(mlx, -(mlx->player.dir.x * mlx->player.movespeed));
	if (key == KEY_A)
		rotate_player(5.0f / 180.0f * M_PI, mlx);
	if (key == KEY_D)
		rotate_player(-5.0f / 180.0f * M_PI, mlx);
	mlx_draw(mlx);
	return (0);
}

void				start(t_mlx *mlx)
{
	mlx->player.cam.x = 0;
	mlx->player.cam.y = 0.66f;
	mlx->player.dir.x = -1.0f;
	mlx->player.dir.y = 0;
	mlx->player.movespeed = 0.1f;
	mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
