/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:39:09 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/21 15:52:11 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		ft_init_fractal_thread(t_mlx *mx, t_fractal *fractal)
{
	int		i;

	i = -1;
	while (++i < mx->cores + 1)
	{
		mx->fractals[i] = fractal + i;
		mx->fractals[i]->x_start = (float)(WIDTH / mx->cores) * i;
		mx->fractals[i]->x_end = (float)(WIDTH / mx->cores) * (i + 1);
		mx->fractals[i]->y_start = 0;
		mx->fractals[i]->y_end = HEIGHT;
	}
	return (1);
}

static void		show_errors_args(void)
{
	ft_putstr_fd("fractol: Wrong args\nOptions:\n", 2);
	ft_putstr_fd("1 - Mandlebrot\n2 - Julia\n3 - Burning Ship\n", 2);
}

int				main(int argc, char **argv)
{
	t_mlx			mx;
	t_fractal		fractal[16];
	int				thread;

	thread = (argc > 2) ? ft_atoi(argv[2]) : 0;
	if (argc < 2 || ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 3)
		show_errors_args();
	else if (ft_init_mlx(&mx, fractal, thread))
		ft_putstr_fd("fractol: mlx_init Fail\n", 2);
	else
	{
		ft_init_fractal(&mx, fractal, ft_atoi(argv[1]), 0);
		ft_init_fractal_thread(&mx, fractal);
		ft_display(&mx);
		mlx_hook(mx.win, 2, 1, &key_press_hook, &mx);
		mlx_hook(mx.win, 3, 2, &key_release_hook, &mx);
		mlx_hook(mx.win, 6, (1L << 6), &mouse_hook, &mx);
		mlx_hook(mx.win, 4, (1L << 2), &mouse_btn_hook, &mx);
		mlx_hook(mx.win, 17, 0, &window, &mx);
		mlx_loop_hook(mx.mlx, &key_loop_hook, &mx);
		mlx_expose_hook(mx.win, ft_towin, &mx);
		mlx_loop(mx.mlx);
	}
	return (0);
}
