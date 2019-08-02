#include "wolf.h"

int    get_textures(t_mlx *mlx)
{
    if (mlx)
        ;
    return (0);
}

static int	map_allot(t_map *map)
{
	if (!(map->matrix = ft_memalloc(sizeof(int) * map->height * map->width)))
		return (fail(-1, "error: can't malloc vox"));
	return (1);
}

static int	check_map(t_map *map, char *mname)
{
	int		fd;
	char	*line;

	line = NULL;
	ft_bzero(map, sizeof(t_map));
	if (0 > (fd = open(mname, O_RDONLY)))
		return (fail(0, "error: cannot open map\n"));
	if (!(get_next_line(fd, &line)))
		return (fail(0, "error: read error\n"));
	map->width = ft_cntwords(line, ' ');
	map->height++;
	free(line);
	while (get_next_line(fd, &line))
	{
		if (!(map->width == ft_cntwords(line, ' ')))
		{
			return (fail(0, "error: bad map formatting"));
		}
		map->height++;
		free(line);
	}
	return (1);
}

static int	splint(t_mlx *mlx, int row, char **strs)
{
	int		i;
	bool	fail;
	t_map	*map;

	map = &mlx->map;
	fail = false;
	i = -1;
	if (row != 0 && row != map->height - 1 && (*strs[0] != '1' || *(strs[map->width - 1]) != '1'))
		fail = true;
	while (++i < map->width)
	{
		*((map->matrix) + (map->width * row + i)) = ft_atoi(strs[i]);
		if ((row == 0 || row == map->height - 1) && *((map->matrix) + (map->width * row + i)) != 1)
			fail = true;
		if (*((map->matrix) + (map->width * row + i)) == 0 && !mlx->player.x && !mlx->player.y)
		{
			mlx->player.x = i + 0.5f;
			mlx->player.y = row + 0.5f;
		}
		free(strs[i]);
	}
	return (fail ? 0 : 1);
}

void		map_destroy(t_map *map)
{
	if (map && map->matrix)
		free(map->matrix);
}

int    get_map(int ac, char **av, t_mlx *mlx)
{
    int i;
    int fd;
    char *line;

    if (ac < 2)
        return (fail(1, "usage: ./wolf3d mappath"));
    if (!check_map(&(mlx->map), av[1]))
		return (1);
	if (0 > map_allot(&(mlx->map)))
		return (fail(1, "error: map alloc"));
	if (0 > (fd = open(av[1], O_RDONLY)))
		return (fail(1, "error: can't open file"));
	i = 0;
	ft_memset(&mlx->player, 0, sizeof(t_player));
	ft_printf("map width: %d map height: %d\n", mlx->map.width, mlx->map.height);
	while (i < mlx->map.height)
	{
		get_next_line(fd, &line);
		ft_printf("%s\n", line);
		if (!splint(mlx, i, ft_strsplit(line, ' ')))
		{
			free(line);
			return (fail(1, "format err"));
		}
		i++;
	}
	if (!mlx->player.x && !mlx->player.y)
		return (fail(1, "starting pos not found"));
	mlx->player.x = 5.5f;
	mlx->player.y = 5.5f;
	printf("player: x(%f) y(%f)\n", mlx->player.x, mlx->player.y);
	return (0);
}