/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:44:17 by calamber          #+#    #+#             */
/*   Updated: 2019/08/07 04:57:52 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# include "colors.h"
# include "keycode_mac.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

# define USE_TEX 1
# define BOUNDS 0
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))
# define TEXTURE_NB 8

pthread_mutex_t				g_lock;

typedef struct				s_map
{
	int	width;
	int	height;
	int	*matrix;
}							t_map;

typedef struct				s_vect_3
{
	double					x;
	double					y;
	double					z;
}							t_vect_3;

typedef struct				s_image
{
	void					*image;
	char					*ptr;
	int						bpp;
	int						stride;
	int						width;
	int						height;
	int						endian;
}							t_image;

typedef struct				s_ray
{
	int						hit;
	double					dirx;
	double					diry;
	double					stepx;
	double					stepy;
	double					sidex;
	double					sidey;
	int						mx;
	int						my;
	double					deltax;
	double					deltay;
	double					dist;
	double					wall;
	int						height;
	t_image					*texture;
	t_vect_3				tex_pos;
}							t_ray;

typedef struct				s_player
{
	double					x;
	double					y;
	t_vect_3				dir;
	t_vect_3				cam;
	double					movespeed;
}							t_player;

typedef struct				s_mlx
{
	void					*mlx;
	void					*window;
	t_image					*image;
	t_image					*tex[TEXTURE_NB];
	t_player				player;
	t_map					map;
}							t_mlx;

typedef struct				s_thread_args
{
	int						start;
	t_mlx					*mlx;
}							t_thread_args;

void						mlx_draw(t_mlx *mlx);
void						mlxdel(t_mlx *mlx);
int							fail(int ret, char *note);
void						start(t_mlx *mlx);
t_image						*new_image(t_mlx *mlx);
t_image						*del_image(t_mlx *mlx, t_image *img);
void						clear_image(t_image *image);
void						image_set_pixel(t_image *image, int x,
								int y, int color);
void						cam_reset(t_mlx *mlx);
void						cam_scale(t_mlx *mlx, int x, int y, int arg);
int							get_map(char **av, t_mlx *mlx);
int							get_textures(t_mlx *mlx);
int							init_it(char *title, t_mlx *mlx);
void						map_destroy(t_map *map);
t_image						*xpm_image(char *xpm, t_mlx *mlx);
void						draw_column(int x, t_mlx *mlx, t_ray *ray);
#endif
