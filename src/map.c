/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 23:19:48 by calamber          #+#    #+#             */
/*   Updated: 2019/08/06 01:52:50 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
			return (fail(0, "error: bad map formatting"));
		map->height++;
		free(line);
	}
	return (1);
}

static int	splint(t_mlx *mlx, int row, char **strs)
{
	int		i;
	bool	fail;

	fail = false;
	i = -1;
	if (row != 0 && row != mlx->map.height - 1 &&
		(*strs[0] != '1' || *(strs[mlx->map.width - 1]) != '1'))
		fail = true;
	while (++i < mlx->map.width)
	{
		*((mlx->map.matrix) + (mlx->map.width * row + i)) = ft_atoi(strs[i]);
		if ((row == 0 || row == mlx->map.height - 1) && *((mlx->map.matrix)
			+ (mlx->map.width * row + i)) != 1)
			fail = true;
		if (*((mlx->map.matrix) + (mlx->map.width * row + i)) == 0 &&
			!mlx->player.x && !mlx->player.y)
		{
			mlx->player.x = i + 0.5f;
			mlx->player.y = row + 0.5f;
		}
		free(strs[i]);
	}
	free(strs);
	return (fail ? 0 : 1);
}

void		map_destroy(t_map *map)
{
	if (map && map->matrix)
		free(map->matrix);
}

int			get_map(char **av, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*line;

	if (!check_map((&mlx->map), av[1]))
		return (0);
	if (0 > map_allot((&mlx->map)))
		return (fail(0, "error: map alloc"));
	if (0 > (fd = open(av[1], O_RDONLY)))
		return (fail(0, "error: can't open file"));
	i = -1;
	while (++i < mlx->map.height)
	{
		get_next_line(fd, &line);
		ft_printf("%s\n", line);
		if (!splint(mlx, i, ft_strsplit(line, ' ')))
		{
			free(line);
			return (fail(0, "format err"));
		}
		free(line);
	}
	printf("player x %f player y %f\n", mlx->player.x, mlx->player.y);
	if (!mlx->player.x && !mlx->player.y)
		return (fail(0, "starting pos not found"));
	return (1);
}
