/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 20:29:19 by kperreau          #+#    #+#             */
/*   Updated: 2015/01/15 20:03:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_write_s(t_options *opt, wchar_t *s)
{
	int				len;
	int				i;
	int				j;
	int				bytes;
	unsigned char	mask[4];

	if ((len = ft_utflen(s)) < 0)
		return (-1);
	len = (opt->precise != -1 && len > opt->precise) ? \
		ft_utfnlen(s, opt->precise) : len;
	if (opt->len > len && !(opt->flags & 1))
		ft_putspace(opt, len, 0);
	j = 0;
	while (j < len)
	{
		bytes = ft_utfclen(*s);
		ft_to_utf8(*s++, bytes, mask);
		i = 0;
		while (i < bytes)
			write(1, &mask[i++], 1);
		j += bytes;
	}
	if (opt->len > len && opt->flags & 1)
		ft_putspace(opt, len, 0);
	return ((opt->len != -1 && len < opt->len) ? opt->len : len);
}

static int	ft_write_s_bis(t_options *opt, char *s)
{
	int		len;

	len = ft_strlen(s);
	len = (opt->precise != -1 && len > opt->precise) ? opt->precise : len;
	if (opt->len > len && !(opt->flags & 1))
		ft_putspace(opt, len, 0);
	write(1, s, len);
	if (opt->len > len && opt->flags & 1)
		ft_putspace(opt, len, 0);
	len = (opt->len != -1 && len < opt->len) ? opt->len : len;
	return (len);
}

int			ft_s(t_options *opt, va_list *ap, int *ret)
{
	wchar_t		*s;
	char		*s2;
	int			value;

	s = NULL;
	s2 = NULL;
	if (opt->modif == 1)
	{
		if ((s = va_arg(*ap, wchar_t *)))
			value = ft_write_s(opt, s);
	}
	else
	{
		if ((s2 = va_arg(*ap, char *)))
			value = ft_write_s_bis(opt, s2);
	}
	if (!s && !s2)
	{
		s2 = ft_strdup("(null)");
		value = ft_write_s_bis(opt, s2);
		free(s2);
	}
	*ret += value;
	return (value);
}

int			ft_s2(t_options *opt, va_list *ap, int *ret)
{
	opt->modif = 1;
	opt->type = 0;
	return (ft_s(opt, ap, ret));
}

int			ft_r(t_options *opt, va_list *ap, int *ret)
{
	char		*s;
	int			value;

	s = NULL;
	if ((s = va_arg(*ap, char *)))
	{
		s = ft_strdup(s);
		ft_strrev(s);
		value = ft_write_s_bis(opt, s);
		free(s);
	}
	else
	{
		s = ft_strdup(")llun(");
		value = ft_write_s_bis(opt, s);
		free(s);
	}
	*ret += value;
	return (value);
}
