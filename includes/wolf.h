/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:44:17 by calamber          #+#    #+#             */
/*   Updated: 2019/08/01 00:58:25 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# include "colors.h"
# include "keycode_mac.h"
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MENU_WIDTH 100
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))

pthread_mutex_t				g_lock;

typedef struct				s_map
{
	int	width;
	int	height;
	int	*matrix;
}							t_map;

typedef struct				s_vect_2
{
	double					x;
	double					y;
}							t_vect_2;

typedef struct				s_image
{
	void					*image;
	char					*ptr;
	int						bpp;
	int						stride;
	int						endian;
}							t_image;

typedef struct				s_cam
{
	double					offsetx;
	double					offsety;
	double					x;
	double					y;
}							t_cam;

typedef struct				s_mlx
{
	void					*mlx;
	void					*window;
	t_image					*image;
	t_cam					*cam;
	t_map					map;
}							t_mlx;

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
int							get_map(int ac, char **av, t_mlx *mlx);
int							get_textures(t_mlx *mlx);

#endif
