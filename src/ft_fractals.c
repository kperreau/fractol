/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 18:59:19 by kperreau          #+#    #+#             */
/*   Updated: 2016/05/30 18:30:56 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_set_pixel(char *data, int x, int y, t_fractal *f)
{
	int		*p_data;
	int		adjust;

	p_data = (void *)(data + x * 4 + y * 4 * WIDTH);
	if (f->i == f->iter_max)
		*p_data = 0;
	else if (f->i < f->iter_max / 2)
		*p_data = (int)(f->i * f->color.var * 0xff / f->iter_max);
	else
	{
		adjust = 255 - f->i / 2;
		*p_data = ((int)(adjust * (f->color.b * f->color.var)) << 16) + \
			((int)(adjust * (f->color.g * f->color.var)) << 8) + \
			(int)(adjust * (f->color.r * f->color.var));
	}
}

void			ft_mandelbrot(t_mlx *mx, t_fractal *f)
{
	double		x;
	double		y;
	double		tmp;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		f->c_r = (x - WIDTH / 2) * f->z + f->x + f->h;
		while (++y < HEIGHT)
		{
			f->c_i = (y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_i = 0;
			f->z_r = 0;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * f->z_i * tmp + f->c_i;
			}
			ft_set_pixel(mx->data, x, y, f);
		}
	}
}

void			ft_julia(t_mlx *mx, t_fractal *f)
{
	double		x;
	double		y;
	double		tmp;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		f->c_r = 0.285;
		while (++y < HEIGHT)
		{
			f->c_i = 0.01 * mx->fractal->var;
			f->z_i = (y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_r = (x - WIDTH / 2) * f->z + f->x + f->h;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * f->z_i * tmp + f->c_i;
			}
			ft_set_pixel(mx->data, x, y, f);
		}
	}
}

void			ft_burningship(t_mlx *mx, t_fractal *f)
{
	double		x;
	double		y;
	double		tmp;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		f->c_r = (x - WIDTH / 2) * f->z + f->x + f->h;
		while (++y < HEIGHT)
		{
			f->c_i = (y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_i = 0;
			f->z_r = 0;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * fabs(f->z_i) * fabs(tmp) + f->c_i;
			}
			ft_set_pixel(mx->data, x, y, f);
		}
	}
}
