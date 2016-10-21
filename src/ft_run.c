/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 18:10:26 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/21 15:49:04 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

static void		ft_put_mlx_str(t_mlx *mx)
{
	char	*iter;
	char	*str;

	iter = ft_itoa(mx->fractal->iter_max);
	str = ft_strjoin("Iteration max: ", iter);
	free(iter);
	mlx_string_put(mx->mlx, mx->win, 6, 5, 0xffffff, str);
	free(str);
}

static void		ft_copy_fractal(t_mlx *mx)
{
	int		i;

	i = 0;
	while (++i < mx->cores)
	{
		mx->fractals[i]->mlx = mx;
		mx->fractals[i]->x = mx->fractal->x;
		mx->fractals[i]->y = mx->fractal->y;
		mx->fractals[i]->z = mx->fractal->z;
		mx->fractals[i]->v = mx->fractal->v;
		mx->fractals[i]->h = mx->fractal->h;
		mx->fractals[i]->type = mx->fractal->type;
		mx->fractals[i]->var = mx->fractal->var;
		mx->fractals[i]->iter_max = mx->fractal->iter_max;
		mx->fractals[i]->color.r = mx->fractal->color.r;
		mx->fractals[i]->color.g = mx->fractal->color.g;
		mx->fractals[i]->color.b = mx->fractal->color.b;
		mx->fractals[i]->color.var = mx->fractal->color.var;
	}
}

int				ft_towin(t_mlx *mx)
{
	mlx_put_image_to_window(mx->mlx, mx->win, mx->img, 0, 0);
	ft_put_mlx_str(mx);
	return (0);
}

void			ft_display(t_mlx *mx)
{
	pthread_t		t[16];
	int				i;

	i = -1;
	ft_copy_fractal(mx);
	if (mx->fractal->type == 1)
		while (++i < mx->cores)
			pthread_create(t + i, NULL, ft_mandelbrot, mx->fractal + i);
	else if (mx->fractal->type == 2)
		while (++i < mx->cores)
			pthread_create(t + i, NULL, ft_julia, mx->fractal + i);
	else if (mx->fractal->type == 3)
		while (++i < mx->cores)
			pthread_create(t + i, NULL, ft_burningship, mx->fractal + i);
	i = -1;
	while (++i < mx->cores)
		pthread_join(*(t + i), NULL);
	ft_towin(mx);
}
