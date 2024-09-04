/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <rmouduri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:59:20 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 03:27:54 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_putchar_ret(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_empty(t_inf inf)
{
	int	ret;

	ret = 0;
	if (inf.form_nb && inf.prec_nb > 0)
		while (inf.prec_nb-- > 0)
			ret += write(1, " ", 1);
	else if (inf.form_nb && inf.prec_nb < 0)
		while (inf.prec_nb++ < 0)
			ret += write(1, " ", 1);
	return (ret);
}

int	ft_putstr_null(t_inf inf, int to_write)
{
	int		ret;
	char	*str;

	str = "(null)";
	inf.form_dot = inf.prec_dot < 0 ? 0 : inf.form_dot;
	ret = 0;
	if (inf.prec_nb >= 0)
	{
		if (inf.form_nb && inf.prec_nb)
			while (to_write-- > 0)
				ret += write(1, " ", 1);
		while (*str && (inf.form_dot ? inf.prec_dot-- > 0 : *str))
			ret += write(1, str++, 1);
	}
	else
	{
		while (*str && (inf.form_dot ? inf.prec_dot-- > 0 : *str))
			ret += write(1, str++, 1);
		if (inf.form_nb && inf.prec_nb)
			while (to_write++ < 0)
				ret += write(1, " ", 1);
	}
	return (ret);
}

int	ft_putstr_ret(t_inf inf, char *str, int to_write)
{
	int	ret;

	ret = 0;
	if (inf.form_nb && inf.prec_nb > 0)
	{
		while (inf.prec_nb-- > to_write)
			ret += write(1, " ", 1);
		inf.form_nb = 0;
	}
	if (inf.form_dot && inf.prec_dot < ft_strlen(str))
		while (str && inf.prec_dot-- > 0)
			ret += write(1, str++, 1);
	else
		ret += write(1, str, ft_strlen(str));
	if (ft_strlen(str) && inf.form_nb && inf.prec_nb < 0)
		while (inf.prec_nb++ < to_write * -1)
			ret += write(1, " ", 1);
	return (ret);
}
