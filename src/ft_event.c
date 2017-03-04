/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 18:58:11 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/21 16:07:48 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				key_press_hook(int keycode, t_mlx *mx)
{
	if (keycode == EXIT)
		exit(0);
	if (keycode == MORE)
		mx->more = 1;
	if (keycode == LESS)
		mx->less = 1;
	if (keycode == TOP)
		mx->top = 1;
	if (keycode == BOTTOM)
		mx->bottom = 1;
	if (keycode == LEFT)
		mx->left = 1;
	if (keycode == RIGHT)
		mx->right = 1;
	if (keycode == I_MORE)
		mx->i_more = 1;
	if (keycode == I_LESS)
		mx->i_less = 1;
	if (keycode == SCREEN)
		ft_tofile(mx->data);
	if (keycode == L)
		mx->lock ^= 1;
	if (keycode == 18 || keycode == 19 || keycode == 20 || keycode == RESET)
		sub_key_press_hook(keycode, mx);
	return (0);
}

int				key_release_hook(int keycode, t_mlx *mx)
{
	if (keycode == TOP)
		mx->top = 0;
	if (keycode == BOTTOM)
		mx->bottom = 0;
	if (keycode == LEFT)
		mx->left = 0;
	if (keycode == RIGHT)
		mx->right = 0;
	if (keycode == MORE)
		mx->more = 0;
	if (keycode == LESS)
		mx->less = 0;
	if (keycode == I_MORE)
		mx->i_more = 0;
	if (keycode == I_LESS)
		mx->i_less = 0;
	return (0);
}

int				mouse_hook(int x, int y, t_mlx *mx)
{
	if ((100 * (clock() - mx->clock_var)) / CLOCKS_PER_SEC > 1)
	{
		mx->mouse.x = x;
		mx->mouse.y = y;
		if (mx->fractal->type == 2 && !mx->lock)
		{
			mx->fractal->var = (mx->mouse.x + mx->mouse.y) / 10;
			ft_display(mx);
		}
		mx->clock_var = clock();
	}
	return (0);
}

int				mouse_btn_hook(int key, int x, int y, t_mlx *mx)
{
	mx->mouse.x = x;
	mx->mouse.y = y;
	if ((30 * (clock() - mx->clock_z)) / CLOCKS_PER_SEC > 1)
	{
		if (key == 4 || key == 1)
		{
			mx->fractal->z /= 1.4;
			mx->fractal->h += (mx->mouse.x - WIDTH / 2) * mx->fractal->z / 2.5;
			mx->fractal->v += (mx->mouse.y - HEIGHT / 2) * mx->fractal->z / 2.5;
			ft_display(mx);
		}
		else if (key == 5 || key == 2)
		{
			mx->fractal->z *= 1.4;
			ft_display(mx);
		}
		mx->clock_z = clock();
	}
	return (0);
}

int				key_loop_hook(t_mlx *mx)
{
	if (mx->top || mx->bottom || mx->right || mx->left ||
		mx->more || mx->less || mx->i_less || mx->i_more)
	{
		if (mx->top)
			mx->fractal->v -= 6 * mx->fractal->z;
		if (mx->bottom)
			mx->fractal->v += 6 * mx->fractal->z;
		if (mx->left)
			mx->fractal->h -= 6 * mx->fractal->z;
		if (mx->right)
			mx->fractal->h += 6 * mx->fractal->z;
		if (mx->more)
			mx->fractal->z /= 1.5;
		if (mx->less && mx->fractal->z < 1.0 / 255)
			mx->fractal->z *= 1.5;
		if (mx->i_more && mx->fractal->iter_max < 150)
			++mx->fractal->iter_max;
		if (mx->i_less && mx->fractal->iter_max > 30)
			--mx->fractal->iter_max;
		ft_display(mx);
	}
	return (0);
}
