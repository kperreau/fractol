/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:26:29 by kperreau          #+#    #+#             */
/*   Updated: 2016/06/29 13:25:13 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		window(t_mlx *mx)
{
	(void)mx;
	exit(0);
}

int		sub_key_press_hook(int keycode, t_mlx *mx)
{
	if (keycode == 18)
		ft_init_fractal(mx, mx->fractal, 1, 1);
	else if (keycode == 19)
		ft_init_fractal(mx, mx->fractal, 2, 1);
	else if (keycode == 20)
		ft_init_fractal(mx, mx->fractal, 3, 1);
	if (keycode == RESET)
		ft_init_fractal(mx, mx->fractal, mx->fractal->type, 1);
	return (0);
}
