#include "wolf.h"

int fail(int ret, char *note)
{
    ft_printf("%s\n", note);
    return (ret);
}

int main(int ac, char **av)
{
    t_mlx   mlx;

    ft_memset(&mlx, 0, sizeof(t_mlx));
    mlx.map = ft_memalloc(sizeof(t_map));
	mlx.player = ft_memalloc(sizeof(t_player));
    if (get_map(ac, av, &mlx) || get_textures(&mlx) || init_it("wolf3d", &mlx))
        return(0);
    for (int y = 0; y < mlx.map->width; y++)
    {
        for (int x = 0; x < mlx.map->width; x++)
            ft_printf("%d", *(mlx.map->matrix + (mlx.map->width * y + x)));
        ft_printf("\n");
    }
    ft_printf("playerx %f player7 %f\n", mlx.player->x, mlx.player->y);
    start(&mlx);
    return (0);
}