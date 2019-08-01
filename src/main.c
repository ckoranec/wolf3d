#include "wolf.h"

int main(int ac, char **av)
{
    t_mlx   mlx;

    validate_map(ac, av, &mlx);
    get_textures(&mlx);
    start(&mlx);
    return (0);
}