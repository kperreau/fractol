/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:39:09 by kperreau          #+#    #+#             */
/*   Updated: 2016/06/29 13:16:20 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				main(int argc, char **argv)
{
	t_mlx			mx;
	t_fractal		fractal;

	(void)argv;
	if (argc != 2 || ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 3)
	{
		ft_putstr_fd("fractol: Wrong args\nOptions:\n", 2);
		ft_putstr_fd("1 - Mandlebrot\n2 - Julia\n3 - Burning Ship\n", 2);
	}
	else if (ft_init_mlx(&mx, &fractal, ft_atoi(argv[1])))
		ft_putstr_fd("fractol: mlx_init Fail\n", 2);
	else
	{
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
