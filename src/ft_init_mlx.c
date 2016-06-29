/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 18:06:07 by kperreau          #+#    #+#             */
/*   Updated: 2016/05/30 19:08:04 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_init_fractal(t_mlx *mx, t_fractal *f, char type, int disp)
{
	mx->fractal = f;
	mx->fractal->x = (type == 1) ? -0.6 : 0;
	mx->fractal->y = 0;
	mx->fractal->z = (type == 3) ? 1.0 / 210 : 1.0 / 256;
	mx->fractal->v = (type == 3) ? -0.4 : 0;
	mx->fractal->h = (type == 3) ? -0.4 : 0;
	mx->fractal->type = type;
	mx->fractal->var = 1;
	mx->fractal->iter_max = 30;
	mx->fractal->color.r = 8;
	mx->fractal->color.g = 4;
	mx->fractal->color.b = 2;
	mx->fractal->color.var = 1;
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

int				ft_init_mlx(t_mlx *mx, t_fractal *fractal, char type)
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
	ft_key_init_mlx(mx);
	mx->data = mlx_get_data_addr(mx->img, &mx->bpp, &width, &mx->endian);
	ft_init_fractal(mx, fractal, type, 0);
	return (0);
}
