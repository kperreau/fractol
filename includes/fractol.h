/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:40:01 by kperreau          #+#    #+#             */
/*   Updated: 2016/06/29 13:17:10 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <float.h>

/*
**PERSONNAL VARS
*/
# define NAME "fractol"
# define WIDTH 600
# define HEIGHT 600

/*
** KEY DEFINE
*/
# define TOP 126
# define BOTTOM 125
# define LEFT 123
# define RIGHT 124
# define MORE 69
# define LESS 78
# define I_MORE 24
# define I_LESS 27
# define EXIT 53
# define SCREEN 96
# define RESET 115
# define L 37

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_color
{
	char		r;
	char		g;
	char		b;
	float		var;
}				t_color;

typedef struct	s_img
{
	int			height;
	int			width;
	char		**data;
}				t_img;

typedef struct	s_fractal
{
	t_color		color;
	size_t		iter_max;
	size_t		i;
	char		type;
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
	double		z;
	double		v;
	double		h;
	double		x;
	double		y;
	double		var;
}				t_fractal;

typedef struct	s_mlx
{
	t_fractal	*fractal;
	t_coord		mouse;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			endian;
	int			height;
	int			width;
	int			top;
	int			bottom;
	int			left;
	int			right;
	int			screen;
	int			less;
	int			more;
	int			i_less;
	int			i_more;
	int			lock;
	clock_t		clock_z;
}				t_mlx;

/*
**BMP
*/
typedef struct	s_hbmp
{
	uint32_t	size;
	uint16_t	r1;
	uint16_t	r2;
	uint32_t	offset;
}				t_hbmp;

typedef struct	s_hwbm
{
	uint32_t	hsize;
	int32_t		width;
	int32_t		height;
	uint16_t	nc;
	uint16_t	bpp;
	uint32_t	comp;
	uint32_t	img_size;
	uint32_t	hppm;
	uint32_t	vppm;
	uint32_t	nbcolor;
	uint32_t	inbcolor;
}				t_hwbm;

/*
**INIT [MLX|VARS]
*/
int				ft_init_mlx(t_mlx *mx, t_fractal *fractal, char type);
void			ft_init_fractal(t_mlx *mx, t_fractal *f, char type, int disp);

/*
**FUNCTIONS
*/
int				ft_towin(t_mlx *mx);
void			ft_display(t_mlx *mx);
void			ft_tofile(char *img);

/*
**EVENT HOOK
*/
int				key_hook(int keycode, t_mlx *mx);
int				key_press_hook(int keycode, t_mlx *mx);
int				sub_key_press_hook(int keycode, t_mlx *mx);
int				key_release_hook(int keycode, t_mlx *mx);
int				mouse_hook(int x, int y, t_mlx *mx);
int				mouse_btn_hook(int key, int x, int y, t_mlx *mx);
int				key_loop_hook(t_mlx *mx);
int				window(t_mlx *mx);
void			ft_mandelbrot(t_mlx *mx, t_fractal *f);
void			ft_julia(t_mlx *mx, t_fractal *f);
void			ft_burningship(t_mlx *mx, t_fractal *f);

#endif
