#include "wolf.h"

int    get_textures(t_mlx *mlx)
{
    if (mlx)
        ;
    return (true);
}

static int	map_allot(t_map *map)
{
	if (!(map->matrix = ft_memalloc(sizeof(char) * map->height * map->width + 1)))
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

static void	splint(t_map *map, int row, char **strs)
{
	int		i;

	i = -1;
	while (++i < map->width)
	{
		(map->matrix)[map->width * row + i] = ft_atoi(strs[i]);
		free(strs[i]);
	}
	free(strs);
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
        return (fail(0, "usage: ./wolf3d mappath"));
    if (!check_map(&(mlx->map), av[1]))
		return (0);
	if (0 > map_allot(&(mlx->map)))
		return (fail(0, "error: map alloc"));
	if (0 > (fd = open(av[1], O_RDONLY)))
		return (fail(-1, "error: can't open file"));
	i = 0;
	while (i < mlx->map.height)
	{
		get_next_line(fd, &line);
		ft_printf("%s\n", line);
		splint(&(mlx->map), i, ft_strsplit(line, ' '));
		free(line);
		i++;
	}
	return (true);
}