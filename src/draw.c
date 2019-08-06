#include "wolf.h"

int						colors(int i)
{
	int rgb[5] = { RED, GREEN, GRAY, YELLOW, MIDNIGHT_BLUE};
	return (rgb[i % 5]);
}

void		dda(t_mlx *mlx, int start, int end, int x, int type)
{
	int	dy;
	int	steps;
	int	i;

	dy = (int)end - (int)start;
	steps = abs(dy);
	i = 0;

	printf("dda start %d\n", x);
	printf("steps: %d start %d end %d\n", steps, start, end);
	while (i <= steps)
	{
		image_set_pixel(mlx->image, x, start, colors(type));
		start += dy / (float)steps;
		i++;
	}
	printf("dda done\n");
}

int							texture_pixel(int x, int y, t_ray *r)
{
	if (x < 0 || y < 0 || x >= r->texture->width || y >= r->texture->height)
		return (0);
	return (*(int *)(r->texture->ptr + ((x + y * r->texture->height) *
		r->texture->bpp)));
}

void						dda_temp(t_mlx *mlx, int start, int end, int x, t_ray *ray)
{
	int y = start;
	while (y < end)
	{
		if (ray->texture)
		{
			ray->tex_pos.y = ((y - WIN_HEIGHT * 0.5f + ray->height * 0.5f) *
				ray->texture->height) / ray->height;
		//printf("printing color %d from texture %p\n", texture_pixel(x, y, ray, mlx), ray->texture);
			image_set_pixel(mlx->image, x, y, texture_pixel(ray->tex_pos.x, ray->tex_pos.y, ray));
		}
		else
			image_set_pixel(mlx->image, x, y, colors(ray->tex_pos.z));
		y++;
	}
}

void						draw_column(int x, t_mlx *mlx, t_ray *ray)
{
	//printf("dist %f\n", ray->dist);

	int lineHeight = (int)floor(WIN_HEIGHT / ray->dist);
	ray->height = lineHeight;
	//int lineHeight = (int)(WIN_HEIGHT / (dist * 10));
	int drawStart = (WIN_HEIGHT - lineHeight) / 2; //-lineHeight / 2 + WIN_HEIGHT / 2;
    if(drawStart < 0)
	  	drawStart = 0;
    int drawEnd = drawStart + lineHeight;
    if(drawEnd > WIN_HEIGHT - 1)
		drawEnd = WIN_HEIGHT - 1;
	//if (ray->dist == 0)
	//	dda_temp(mlx, 0, WIN_HEIGHT, x, ray);
	//else
	//	dda_temp(mlx, drawStart, drawEnd, x, ray);
	dda_temp(mlx, drawStart, drawEnd, x, ray);
}

void						cast(int col, t_mlx *mlx)
{
	t_ray		ray;
    t_player	*player;
	double		camera;
	player = &mlx->player;
	double playerx = player->x;
	double playery = player->y;
	double planex = player->cam.x;
	double planey = player->cam.y;


	//printf("pdir x %f pdir y %f\n", mlx->player.dir.x, mlx->player.dir.y);
	//printf("player plane %f %f\n", player->cam.x, player->cam.y);
	//printf("testing map w %d h %d f_w %f f_h %f\n", mlx->map.width, mlx->map.height, (double)mlx->map.width, (double)mlx->map.height);
	int mapx = playerx;
	int mapy = playery;

	camera = 2.0f * col / (double)WIN_WIDTH - 1.0f;
	ray.dirx = mlx->player.dir.x + planex * camera;
	ray.diry = mlx->player.dir.y + planey * camera;
	ray.deltax = sqrt((ray.diry * ray.diry) / (ray.dirx * ray.dirx) + 1);///*ray.dirx == 0 ? 0 : */fabs(1/ray.dirx);
	ray.deltay = sqrt((ray.dirx * ray.dirx) / (ray.diry * ray.diry) + 1);///*ray.diry == 0 ? 0 : */fabs(1/ray.diry);
	ray.stepx = (ray.dirx < 0 ? -1 : 1);
	ray.stepy = (ray.diry < 0 ? -1 : 1);
	ray.sidex = ray.dirx < 0 ? (playerx - mapx) * ray.deltax : (mapx + 1.0f - playerx) * ray.deltax; //(r->x < 0 ? p->x - t.mx : t.mx - p->x + 1) * t.dx;
	ray.sidey = ray.diry < 0 ? (playery - mapy) * ray.deltay : (mapy + 1.0f - playery) * ray.deltay; //working on it(r->y < 0 ? p->y - t.my : t.my - p->y + 1) * t.dy;
	int hit = 0;
	int side;
	//printf("stepx %d stepy %d\n", ray.stepx, ray.stepy);
	//printf("mapx %f mapy %f\n", mapx, mapy);
	//printf("looking\n");
	while (hit == 0)
	{
		if (ray.sidex < ray.sidey)
		{
			ray.sidex += ray.deltax;
			mapx += ray.stepx;
			side = 0;
		}
		else
		{
			ray.sidey += ray.deltay;
			mapy += ray.stepy;
			side = 1;
		}
		//Check if ray has hit a wall
		//printf("checking %f %f\n", mapx, mapy);
		//if (mapx < 0 || mapx > (double)mlx->map.width - 1 || mapy < 0 || mapy > (double)mlx->map.height - 1)
		//	return ;
		//printf("ayy\n");
		hit = *(mlx->map.matrix + (mlx->map.width * (int)floor(mapy) + (int)floor(mapx)));
		//printf("hit %d\n", hit);
		//if (hit != 0)
			//printf("hit! %d at %f %f\n", hit, mapx, mapy);
		//if (mapx < 0 || mapx >= (double)mlx->map.width || mapy < 0 || mapy >= (double)mlx->map.height)
		//	break ;
	}
	//printf("player: x(%f) y(%f)\n", mlx->player.x, mlx->player.y);
	//printf("done looking\n");
	ray.texture = USE_TEX ? mlx->tex[hit] : NULL;
	ray.tex_pos.z = hit;
	if (side == 0)
		ray.dist = (mapx - playerx + (1.0 - ray.stepx) / 2.0) / ray.dirx;
	else
		ray.dist = (mapy - playery + (1.0 - ray.stepy) / 2.0) / ray.diry;
	ray.wall = (side ? player->x + ray.dist * ray.dirx : player->y + ray.dist * ray.diry);
	ray.wall -= floor(ray.wall);
	if (ray.texture)
	ray.tex_pos.x = (int)(ray.wall * ray.texture->width);
	draw_column(col, mlx, &ray);
}

void						*scan_across(void *in)
{
	t_thread_args *args = in;

	pthread_mutex_lock(&g_lock);
	int end = args->start + 240;
	for(int x = args->start; x < end; x++)
    {
		cast(x, args->mlx);
	}
	free(args);
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}

t_thread_args				*make_targs(t_mlx *mlx, int start)
{
	t_thread_args *args;

	args = malloc(sizeof(t_thread_args));
	args->mlx = mlx;
	args->start = start;
	return (args);
}

void						draw_it(t_mlx *mlx)
{
	pthread_t		thread[8];
	int i = 0;
	int x = 0;
	int next;
	if (pthread_mutex_init(&g_lock, NULL) != 0)
		ft_printf("Mutex initialization failed.\n");
	next = WIN_WIDTH / 8;
	while (x < WIN_WIDTH)
	{
		pthread_create(&thread[i], NULL, scan_across, make_targs(mlx, x));
		pthread_join(thread[i], NULL);
		i++;
		x = next;
		next += WIN_WIDTH / 8;
	}
}

void	mlx_draw(t_mlx *mlx)
{
	clear_image(mlx->image);
	draw_it(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
}
