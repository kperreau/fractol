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

void			*ft_mandelbrot(void *data)
{
	t_fractal	*f;

	f = data;
	f->p_x = f->x_start - 1;
	while (++f->p_x < f->x_end)
	{
		f->p_y = f->y_start - 1;
		f->c_r = (f->p_x - WIDTH / 2) * f->z + f->x + f->h;
		while (++f->p_y < f->y_end)
		{
			f->c_i = (f->p_y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_i = 0;
			f->z_r = 0;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				f->tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * f->z_i * f->tmp + f->c_i;
			}
			ft_set_pixel(f->mlx->data, f->p_x, f->p_y, f);
		}
	}
	return (NULL);
}

void			*ft_julia(void *data)
{
	t_fractal	*f;

	f = data;
	f->p_x = f->x_start - 1;
	while (++f->p_x < f->x_end)
	{
		f->p_y = f->y_start - 1;
		f->c_r = 0.285;
		while (++f->p_y < f->y_end)
		{
			f->c_i = 0.01 * f->var;
			f->z_i = (f->p_y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_r = (f->p_x - WIDTH / 2) * f->z + f->x + f->h;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				f->tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * f->z_i * f->tmp + f->c_i;
			}
			ft_set_pixel(f->mlx->data, f->p_x, f->p_y, f);
		}
	}
	return (NULL);
}

void			*ft_burningship(void *data)
{
	t_fractal	*f;

	f = data;
	f->p_x = f->x_start - 1;
	while (++f->p_x < f->x_end)
	{
		f->p_y = f->y_start - 1;
		f->c_r = (f->p_x - WIDTH / 2) * f->z + f->x + f->h;
		while (++f->p_y < f->y_end)
		{
			f->c_i = (f->p_y - HEIGHT / 2) * f->z + f->y + f->v;
			f->z_i = 0;
			f->z_r = 0;
			f->i = -1;
			while (!(++f->i) ||
				(f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->iter_max))
			{
				f->tmp = f->z_r;
				f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
				f->z_i = 2 * fabs(f->z_i) * fabs(f->tmp) + f->c_i;
			}
			ft_set_pixel(f->mlx->data, f->p_x, f->p_y, f);
		}
	}
	return (NULL);
}
