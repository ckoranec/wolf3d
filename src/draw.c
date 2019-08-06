/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 23:20:55 by calamber          #+#    #+#             */
/*   Updated: 2019/08/06 00:12:32 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				step_ray(t_ray *ray, t_player *p, t_mlx *mlx)
{
	int side;

	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidex < ray->sidey)
		{
			ray->sidex += ray->deltax;
			ray->mx += ray->stepx;
			side = 0;
		}
		else
		{
			ray->sidey += ray->deltay;
			ray->my += ray->stepy;
			side = 1;
		}
		ray->hit = *(mlx->map.matrix + (mlx->map.width *
			(int)floor(ray->my) + (int)floor(ray->mx)));
	}
	ray->dist = side == 0 ? (ray->mx - p->x + (1.0 - ray->stepx) / 2.0)
	/ ray->dirx : (ray->my - p->y + (1.0 - ray->stepy) / 2.0) / ray->diry;
	ray->wall = (side ? p->x + ray->dist * ray->dirx :
		p->y + ray->dist * ray->diry);
	ray->texture = USE_TEX ? mlx->tex[ray->hit] : NULL;
}

void				cast(int col, t_mlx *mlx)
{
	t_ray		ray;
	t_player	*p;
	double		camera;

	p = &mlx->player;
	ray.mx = p->x;
	ray.my = p->y;
	camera = 2.0f * col / (double)WIN_WIDTH - 1.0f;
	ray.dirx = mlx->player.dir.x + p->cam.x * camera;
	ray.diry = mlx->player.dir.y + p->cam.y * camera;
	ray.deltax = sqrt((ray.diry * ray.diry) / (ray.dirx * ray.dirx) + 1);
	ray.deltay = sqrt((ray.dirx * ray.dirx) / (ray.diry * ray.diry) + 1);
	ray.stepx = (ray.dirx < 0 ? -1 : 1);
	ray.stepy = (ray.diry < 0 ? -1 : 1);
	ray.sidex = ray.dirx < 0 ? (p->x - ray.mx) * ray.deltax :
		(ray.mx + 1.0f - p->x) * ray.deltax;
	ray.sidey = ray.diry < 0 ? (p->y - ray.my) * ray.deltay :
		(ray.my + 1.0f - p->y) * ray.deltay;
	step_ray(&ray, p, mlx);
	ray.wall -= floor(ray.wall);
	if (ray.texture)
		ray.tex_pos.x = (int)(ray.wall * ray.texture->width);
	draw_column(col, mlx, &ray);
}

void				*draw_it(void *in)
{
	t_thread_args	*args;
	int				end;

	args = in;
	pthread_mutex_lock(&g_lock);
	end = args->start + (WIN_WIDTH / 8);
	while (args->start < end)
	{
		cast(args->start, args->mlx);
		args->start++;
	}
	free(args);
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}

t_thread_args		*make_targs(t_mlx *mlx, int start)
{
	t_thread_args *args;

	args = ft_memalloc(sizeof(t_thread_args));
	args->mlx = mlx;
	args->start = start;
	return (args);
}

void				mlx_draw(t_mlx *mlx)
{
	pthread_t	thread[8];
	int			i;
	int			x;
	int			next;

	i = 0;
	x = 0;
	clear_image(mlx->image);
	if (pthread_mutex_init(&g_lock, NULL) != 0)
		ft_printf("Mutex initialization failed.\n");
	next = WIN_WIDTH / 8;
	while (x < WIN_WIDTH)
	{
		pthread_create(&thread[i], NULL, draw_it, make_targs(mlx, x));
		pthread_join(thread[i], NULL);
		i++;
		x = next;
		next += WIN_WIDTH / 8;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	mlx_string_put(mlx->mlx, mlx->window, 10,
		WIN_HEIGHT - 30, WHITE, "ESC: close");
}
