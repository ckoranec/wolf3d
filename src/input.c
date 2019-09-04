/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/09/04 00:54:03 by calamber         ###   ########.fr       */
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
	t_vect_3	*pdir;
	t_vect_3	new;

	pdir = &mlx->player.dir;
	new.x = mlx->player.x + (amount * pdir->x);
	new.y = mlx->player.y + (amount * pdir->y);
	mlx->player.x = !(BOUNDS && *(mlx->map.matrix + (mlx->map.width *
		(int)floor(mlx->player.y) + (int)floor(new.x)))) ? new.x : mlx->player.x;
	mlx->player.y = !(BOUNDS && *(mlx->map.matrix + (mlx->map.width *
		(int)floor(new.y) + (int)floor(mlx->player.x)))) ? new.y : mlx->player.y;
}

int			base_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_UP)
		move_player(mlx, mlx->player.movespeed);
	if (key == KEY_DOWN)
		move_player(mlx, -mlx->player.movespeed);
	if (key == KEY_LEFT)
		rotate_player(5.0f / 180.0f * M_PI, mlx);
	if (key == KEY_RIGHT)
		rotate_player(-5.0f / 180.0f * M_PI, mlx);
	if (key == KEY_ESCAPE)
		push_mode_stack(init_menu, mlx);
	return (0);
}

static int			main_key_hook(int key, t_mlx *mlx)
{
	if (mlx->mode)
		(mlx->mode->handler)(key, mlx);
	mlx_draw(mlx);
	return (0);
}

int					mlx_loop_tmp(void *param)
{
	if (param)
		;
	printf("in da loop\n");
	return (0);	
}

void				start(t_mlx *mlx)
{
	mlx->player.cam.x = 0.378560f;
	mlx->player.cam.y = -0.540640f;
	mlx->player.dir.x = 0.819152f;
	mlx->player.dir.y = 0.573576f;
	mlx->player.movespeed = 0.1f;
	push_mode_stack(init_main_mode, mlx);
	mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, main_key_hook, mlx);
	//mlx_loop_hook(mlx, mlx_loop_tmp, mlx);
	mlx_loop(mlx->mlx);
	
	printf("yo\n");
}
