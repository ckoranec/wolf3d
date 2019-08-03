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
    ft_memset(&mlx.player, 0, sizeof(t_mlx));
    ft_memset(&mlx.map, 0, sizeof(t_mlx));

    if (!init_it("wolf3d", &mlx))
        return(0);
    if (!get_map(ac, av, &mlx))// || !get_textures(&mlx) || !init_it("wolf3d", &mlx))
        return(0);
    printf("map width: %d map height: %d\n", mlx.map.width, mlx.map.height);
    printf("playerx %f playery %f\n", mlx.player.x, mlx.player.y);
    for (int y = 0; y < mlx.map.height; y++)
    {
        for (int x = 0; x < mlx.map.width; x++)
            ft_printf("%d", *(mlx.map.matrix + (mlx.map.width * y + x)));
        ft_printf("\n");
    }
    start(&mlx);
    return (0);
}