/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 18:06:07 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/21 15:52:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_init_fractal(t_mlx *mx, t_fractal *f, char type, int disp)
{
	f->mlx = mx;
	f->x_start = 0;
	f->x_end = WIDTH;
	f->y_start = 0;
	f->y_end = HEIGHT;
	f->x = (type == 1) ? -0.6 : 0;
	f->y = 0;
	f->z = (type == 3) ? 1.0 / 210 : 1.0 / 256;
	f->v = (type == 3) ? -0.4 : 0;
	f->h = (type == 3) ? -0.4 : 0;
	f->type = type;
	f->var = 1;
	f->iter_max = 30;
	f->color.r = 8;
	f->color.g = 4;
	f->color.b = 2;
	f->color.var = 1;
	if (disp)
		ft_display(mx);
}

static void		ft_key_init_mlx(t_mlx *mx)
{
	mx->top = 0;
	mx->bottom = 0;
	mx->left = 0;
	mx->right = 0;
	mx->screen = 0;
	mx->less = 0;
	mx->more = 0;
	mx->i_more = 0;
	mx->i_less = 0;
	mx->lock = 0;
	mx->mouse.y = (int)(HEIGHT / 2);
	mx->mouse.x = (int)(WIDTH / 2);
}

int				ft_init_mlx(t_mlx *mx, t_fractal *f, int thread)
{
	int		width;

	if (!(mx->mlx = mlx_init()))
		return (1);
	width = WIDTH;
	mx->win = mlx_new_window(mx->mlx, WIDTH, HEIGHT, NAME);
	mx->img = mlx_new_image(mx->mlx, WIDTH, HEIGHT);
	mx->bpp = 24;
	mx->endian = 1;
	mx->height = HEIGHT;
	mx->width = WIDTH;
	mx->clock_z = clock();
	mx->clock_var = clock();
	ft_key_init_mlx(mx);
	mx->data = mlx_get_data_addr(mx->img, &mx->bpp, &width, &mx->endian);
	mx->fractal = f;
	mx->cores = (thread) ? sysconf(_SC_NPROCESSORS_ONLN) : 1;
	mx->cores = (mx->cores > 16) ? 16 : mx->cores;
	return (0);
}
