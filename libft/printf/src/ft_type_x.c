/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 21:22:03 by kperreau          #+#    #+#             */
/*   Updated: 2015/01/15 19:04:58 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int		ft_write_x(t_options *opt, char *hex, unsigned long long n)
{
	int		len;
	int		temp;

	if (opt->len && opt->flags & 8)
		opt->len -= 2;
	if (opt->precise == -1 && opt->zero && opt->flags & 8)
		opt->precise = opt->len;
	temp = (n || opt->precise) ? ft_strlen(hex) : 0;
	len = ((opt->precise > temp) ? opt->precise : temp);
	if (opt->len > len && !(opt->flags & 1))
		ft_putspace(opt, len, 0);
	if (opt->flags & 8 && n && opt->type == 10)
		write(1, "0x", 2);
	else if (opt->flags & 8 && n)
		write(1, "0X", 2);
	if (opt->precise > temp)
		ft_putzero(opt, temp);
	if (opt->precise || n)
		write(1, hex, temp);
	if (opt->len > len && opt->flags & 1)
		ft_putspace(opt, len, 0);
	len = (opt->len > len) ? opt->len : len;
	return ((opt->flags & 8 && n) ? len + 2 : len);
}

int				ft_x(t_options *opt, va_list *ap, int *ret)
{
	unsigned long long	n;
	char				hex[20];

	if (1 << opt->modif & 30)
		n = va_arg(*ap, unsigned long);
	else if (opt->modif == 5)
		n = (unsigned char)va_arg(*ap, unsigned int);
	else
		n = va_arg(*ap, unsigned int);
	ft_dectohex(hex, n, (opt->type == 11) ? 1 : 0);
	*ret += ft_write_x(opt, hex, n);
	return (0);
}

int				ft_x2(t_options *opt, va_list *ap, int *ret)
{
	return (ft_x(opt, ap, ret));
}
