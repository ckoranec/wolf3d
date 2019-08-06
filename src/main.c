/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 23:18:23 by calamber          #+#    #+#             */
/*   Updated: 2019/08/05 23:19:23 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	fail(int ret, char *note)
{
	ft_printf("%s\n", note);
	return (ret);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac < 2)
		return (fail(1, "usage: ./wolf3d mappath"));
	ft_memset(&mlx, 0, sizeof(t_mlx));
	ft_memset(&mlx.player, 0, sizeof(t_player));
	ft_memset(&mlx.map, 0, sizeof(t_map));
	if (!init_it("wolf3d", &mlx))
		return (0);
	if (!get_map(av, &mlx))
		return (0);
	if (!get_textures(&mlx))
		return (0);
	start(&mlx);
	return (0);
}
