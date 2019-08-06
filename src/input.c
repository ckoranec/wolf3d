/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/08/06 02:20:32 by calamber         ###   ########.fr       */
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
	int			hitx;
	int			hity;
	t_vect_3	*pdir;
	t_vect_3	new;

	pdir = &mlx->player.dir;
	new.x = mlx->player.x + (amount * pdir->x);
	new.y = mlx->player.y + (amount * pdir->y);
	if ((new.x < 0 || new.x > mlx->map.width
		|| new.y < 0 || new.y > mlx->map.height) && BOUNDS)
		return ;
	hitx = *(mlx->map.matrix + (mlx->map.width *
		(int)floor(new.x) + (int)floor(mlx->player.y)));
	hity = *(mlx->map.matrix + (mlx->map.width *
		(int)floor(mlx->player.x) + (int)floor(new.y)));
	mlx->player.x = new.x;//hitx ? mlx->player.x : new.x;
	mlx->player.y = new.y;//hity ? mlx->player.y : new.y;
}

static int			fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		mlxdel(mlx);
	if (key == KEY_UP)
		move_player(mlx, mlx->player.movespeed);
	if (key == KEY_DOWN)
		move_player(mlx, -mlx->player.movespeed);
	if (key == KEY_LEFT)
		rotate_player(5.0f / 180.0f * M_PI, mlx);
	if (key == KEY_RIGHT)
		rotate_player(-5.0f / 180.0f * M_PI, mlx);
	mlx_draw(mlx);
	return (0);
}

void				start(t_mlx *mlx)
{
	mlx->player.cam.x = 0.378560f;
	mlx->player.cam.y = -0.540640f;
	mlx->player.dir.x = 0.819152f;
	mlx->player.dir.y = 0.573576f;
	mlx->player.movespeed = 0.2f;
	mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
