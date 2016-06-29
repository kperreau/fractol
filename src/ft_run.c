/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 18:10:26 by kperreau          #+#    #+#             */
/*   Updated: 2016/06/29 12:33:26 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int				ft_towin(t_mlx *mx)
{
	mlx_put_image_to_window(mx->mlx, mx->win, mx->img, 0, 0);
	ft_put_mlx_str(mx);
	return (0);
}

void			ft_display(t_mlx *mx)
{
	if (mx->fractal->type == 1)
		ft_mandelbrot(mx, mx->fractal);
	else if (mx->fractal->type == 2)
		ft_julia(mx, mx->fractal);
	else if (mx->fractal->type == 3)
		ft_burningship(mx, mx->fractal);
	ft_towin(mx);
}
