#include "wolf.h"

int fail(int ret, char *note)
{
    ft_printf("%s\n", note);
    return (ret);
}

int main(int ac, char **av)
{
    t_mlx   mlx;

    if (!(get_map(ac, av, &mlx) || get_textures(&mlx)))
        return(0);
    for (int y = 0; y < mlx.map.width; y++)
        for (int x = 0; x < mlx.map.width; x++)
            ft_printf("%d", mlx.map.matrix + mlx.map.width * y + x);
    ft_printf("\n");
    //start(&mlx);
    return (0);
}