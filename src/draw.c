#include "wolf.h"

int						colors(int i)
{
	int rgb[5] = { RED, GREEN, BLUE, LAVENDER, MIDNIGHT_BLUE};
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

void						draw_column(int x, t_mlx *mlx, double dist, int type)
{
	printf("dist %f\n", dist);
	int lineHeight = (int)(WIN_HEIGHT / dist);

	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
    if(drawStart < 0)
	  	drawStart = 0;
    int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
    if(drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	dda(mlx, drawStart, drawEnd, x, type);
}

void						draw_it(t_mlx *mlx)
{
    t_ray ray;
    t_player *player;
	double		camera;

	
	for(int x = 0; x < WIN_WIDTH; x++)
    {
		player = &mlx->player;
		double playerx = 6.0f;
		double playery = 10.0f;
		printf("pdir x %f pdir y %f", mlx->player.dir_x, mlx->player.dir_y);
		printf("testing map w %d h %d f_w %f f_h %f\n", mlx->map.width, mlx->map.height, (double)mlx->map.width, (double)mlx->map.height);
		double mapx = 6.0f;
		double mapy = 10.0f;
    	double planex = 0;
		double planey = 0.66f;

		camera = 2 * x / (double)mlx->map.width - 1;
		ray.dirx = mlx->player.dir_x + planex * camera;
		ray.diry = mlx->player.dir_y + planey * camera;

		ray.deltax = ray.dirx == 0 ? 0 : fabs(1/ray.dirx);
		ray.deltay = ray.diry == 0 ? 0 : fabs(1/ray.diry);
		ray.stepx = (ray.dirx < 0 ? -1 : 1);
		ray.stepy = (ray.diry < 0 ? -1 : 1);
		ray.sidex = ray.dirx < 0 ? (playerx - mapx) * ray.deltax : (mapx + 1.0f - playerx) * ray.deltax; //(r->x < 0 ? p->x - t.mx : t.mx - p->x + 1) * t.dx;
		ray.sidey = ray.diry < 0 ? (playery - mapy) * ray.deltay : (mapy + 1.0f - playery) * ray.deltay; //working on it(r->y < 0 ? p->y - t.my : t.my - p->y + 1) * t.dy;
		int hit = 0;
		int side;
		printf("stepx %d stepy %d\n", ray.stepx, ray.stepy);
		printf("mapx %f mapy %f\n", mapx, mapy);
		printf("looking\n");
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
				ray.sidey += ray.deltax;
				mapy += ray.stepy;
				side = 1;
			}
			//Check if ray has hit a wall
			printf("checking %f %f\n", mapx, mapy);
			if (mapx >= 0 && mapx < (double)mlx->map.width && mapy >= 0 && mapy < (double)mlx->map.height)
			{
				printf("ayy\n");
				hit = *(mlx->map.matrix + (mlx->map.width * (int)mapy + (int)mapx));
				printf("hit %d\n", hit);
			}
			if (hit != 0)
			{
				printf("hit! %f %f\n", mapx, mapy);
			}
			if (mapx < 0 || mapx >= (double)mlx->map.width || mapy < 0 || mapy >= (double)mlx->map.height)
				break ;
		}
		printf("done looking\n");
		double prepwalldist;
		if (side == 0)
			prepwalldist = (mapx - playerx + (1 - ray.stepx) / 2) / ray.dirx;
		else
			prepwalldist = (mapy - playery + (1 - ray.stepy) / 2) / ray.diry;
		draw_column(x, mlx, prepwalldist, hit);
	}
}

void	mlx_draw(t_mlx *mlx)
{
	clear_image(mlx->image);
	draw_it(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
}
