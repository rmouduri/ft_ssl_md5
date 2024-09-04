/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conversions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <rmouduri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:34:42 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 03:28:12 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

static int	get_int_size(int n)
{
	int	size;

	if (n == -2147483648)
		return (11);
	size = 1;
	if (n < 0)
	{
		++size;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		++size;
	}
	return (size);
}

int			int_conversions(t_inf inf, va_list val)
{
	int		ret;
	int		n;

	n = (int)va_arg(val, int);
	if (n == 0)
		return (write_int_zero(inf));
	ret = get_int_size(n);
	if (inf.form_zero && !inf.form_dot)
		ret += write_zero_flag(inf, ret, n);
	else
		ret += int_write_preflag(inf, ret, n);
	ft_put_lint(n, inf);
	ret += int_write_postflag(inf, ret, n);
	return (ret);
}
