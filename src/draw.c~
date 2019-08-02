#include "wolf.h"

void						mlx_draw(t_mlx *mlx)
{
    if (mlx)
      t_ray ray;
    t_cam camera;
    double raydx = -1, raydy = 0;
    double planex =0, planey = 0.66;
    for(int x; x < map->width; x++)
      {
	camera->x = 2 * x / map->width -1;
	ray->raydirx = raydx + planex *carmera->x;
	ray->raydiry = raydy +planey * camera->x;

	ray->deltax = abs(1/ray->raydirx);
	ray->deltay = abs(1/ray->raydiry);      
}        ;
}
