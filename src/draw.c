#include "wolf.h"

void						mlx_draw(t_mlx *mlx)
{
    if (mlx)
      t_ray ray;
    t_cam camera;
    double raydx = -1, raydy = 0;
    double planex =0, planey = 0.66;
    double perpwall;    
for(int x; x < map->width; x++)
      {
	camera->x = 2 * x / map->width -1;
	ray->raydirx = raydx + planex *carmera->x;
	ray->raydiry = raydy +planey * camera->x;

	ray->deltax = abs(1/ray->raydirx);
	ray->deltay = abs(1/ray->raydiry);      
	ray->stepx = (r->x < 0 ? -1 : 1);
	ray->stepy = (r->y < 0 ? -1 : 1);
	ray=>sidex = (player->x - ray->mx) * ray->deltax ; //(r->x < 0 ? p->x - t.mx : t.mx - p->x + 1) * t.dx;
	ray->sidey =(player->y - ray->my) * ray->deltay; //working on it(r->y < 0 ? p->y - t.my : t.my - p->y + 1) * t.dy;
	  int hit = 0;
	  while(hit == 0)
	    {
	      if (sideDistX < sideDistY)
		{
		  sideDistX += deltaDistX;
		  int mapX += stepX;
		  side = 0;
		}
	      else
		{
		  sideDistY += deltaDistY;
		  int mapY += stepY;
		  side = 1;
		}
	      //Check if ray has hit a wall
	      if (map[y][x] > 0) 
		hit = 1;
	    }
	  if(side == 0)
	    prepwall = (mapx - player->posx + (1 - stepx) / 2) /raydirx;
}        ;
}
