/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 23:27:25 by calamber          #+#    #+#             */
/*   Updated: 2019/08/07 20:31:50 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		colors(int i)
{
	static int rgb[62] = { RED, ORANGE, LIME, BLUE, YELLOW, CYAN, MAGENTA,
	SILVER, GRAY, MAROON, OLIVE, GREEN, PURPLE, TEAL, NAVY, CRIMSON, CORAL,
	INDIAN_RED, SALMON, ORANGE_RED, GOLD, GOLDEN_ROD, SADDLEBROWN, LAWN_GREEN,
	DARK_GREEN, FOREST_GREEN, PALE_GREEN, SPRING_GREEN, SEA_GREEN,
	LIGHT_SEA_GREEN, DARK_SLATE_GRAY, POWDER_BLUE, AQUA_MARINE, STEEL_BLUE,
	SKY_BLUE, MIDNIGHT_BLUE, INDIGO, DARK_MAGENTA, DEEP_PINK, HOT_PINK, ORCHID,
	BEIGE, ANTIQUE_WHITE, WHEAT, CORN_SILK, LAVENDER, FLORAL_WHITE, ALICE_BLUE,
	GHOST_WHITE, HONEYDEW, IVORY, AZURE, SNOW, MISTY_ROSE, DARK_GRAY, GAINSBORO,
	WHITE_SMOKE, DISCO, BRICK_RED, FLAMINGO, JAFFA, SAFFRON };

	return (rgb[i % 62]);
}
/*
int		get_shadow(int pixel, t_mlx *mlx, t_ray *ray)
{
	t_vect_2 player;

	player.x = mlx->player.x;
	player.y = mlx->player.y;

}
*/

int		texture_pixel(int x, int y, t_ray *r)
{
	if (x < 0 || y < 0 || x >= r->texture->width || y >= r->texture->height)
		return (0);
	return (*(int *)(r->texture->ptr + ((x + y * r->texture->height) *
		r->texture->bpp)));
}

void	dda(t_mlx *mlx, t_vect_3 *line, int x, t_ray *ray)
{
	int	y;

	y = line->x;
	while (y < line->y)
	{
		if (ray->texture)
		{
			ray->tex_pos.y = ((y - WIN_HEIGHT * 0.5f + ray->height * 0.5f) *
				ray->texture->height) / ray->height;
			image_set_pixel(mlx->image, x, y, texture_pixel(ray->tex_pos.x,
				ray->tex_pos.y, ray));
		}
		else
			image_set_pixel(mlx->image, x, y, colors(ray->hit));
		y++;
	}
}

void	draw_column(int x, t_mlx *mlx, t_ray *ray)
{
	t_vect_3	line;
	int			start;
	int			end;

	ray->height = (int)floor(WIN_HEIGHT / ray->dist);
	start = (WIN_HEIGHT - ray->height) / 2;
	if (start < 0)
		start = 0;
	end = start + ray->height;
	if (end > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	line.x = start;
	line.y = end;
	dda(mlx, &line, x, ray);
}

int		get_textures(t_mlx *mlx)
{
	static char	*map[TEXTURE_NB] = { "textures/brick_hi.xpm",
		"textures/wood_hi.xpm", "textures/metal_hi.xpm",
		"textures/stone_hi.xpm", "textures/grass_hi.xpm",
		"textures/brick.xpm", "textures/brick.xpm", NULL};
	int			i;

	i = 1;
	while (i < TEXTURE_NB && map[i - 1])
		if (!(mlx->tex[i] = xpm_image(map[i - 1], mlx)))
		{
			i = 0;
			while (i < TEXTURE_NB)
				del_image(mlx, mlx->tex[i++]);
			return (0);
		}
		else
			i++;
	mlx->tex[0] = NULL;
	return (1);
}
