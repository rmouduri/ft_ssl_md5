/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <rmouduri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:09:53 by romain            #+#    #+#             */
/*   Updated: 2020/12/08 16:08:38 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_put_lint(int n, t_inf inf)
{
	if (n == -2147483648 && (inf.form_dot || inf.form_zero))
		return (write(1, "2147483648", 10));
	else if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		if (!inf.form_dot && !inf.form_zero)
			write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		return (ft_put_lint(n / 10, inf) + ft_putchar_ret(n % 10 + 48));
	return (ft_putchar_ret(n % 10 + 48));
}

int	int_write_preflag(t_inf inf, int sizn, int n)
{
	int	ret;
	int	size;

	if (!(ret = 0) && inf.form_nb)
	{
		if (inf.form_dot && inf.prec_dot >= sizn)
			size = inf.prec_nb - sizn - (inf.prec_dot - sizn) -
				(inf.form_hash && inf.form_dot ? 2 : 0);
		else
			size = inf.prec_nb - sizn - (inf.form_hash && inf.form_dot ? 2 : 0);
		while (size-- > (inf.form_dot && n < 0 && inf.prec_dot >= sizn ? 1 : 0))
			ret += write(1, " ", 1);
	}
	ret += write_hash(inf);
	if (inf.form_dot)
	{
		size = inf.prec_dot - sizn + (inf.form_hash ? 2 : 0);
		if (n < 0)
			size += write(1, "-", 1);
		while (size-- > 0)
			ret += write(1, "0", 1);
	}
	return (ret);
}

int	write_zero_flag(t_inf inf, int nb_size, int n)
{
	int	ret;
	int	size;

	ret = 0;
	size = 0;
	if ((inf.conversion == 'x' || inf.conversion == 'X') && inf.form_hash)
	{
		ret += inf.conversion == 'x' ? write(1, "0x", 2) : write(1, "0X", 2);
		size = -2;
	}
	if (n < 0)
		write(1, "-", 1);
	size += inf.prec_zero - nb_size;
	while (size-- > 0)
		ret += write(1, "0", 1);
	return (ret);
}

int	int_write_postflag(t_inf inf, int n_size, int n)
{
	int	ret;
	int	size;

	ret = 0;
	if (inf.form_nb)
	{
		if (inf.form_dot && inf.prec_dot >= n_size)
			size = inf.prec_nb + n_size + (inf.prec_dot - n_size);
		else
			size = inf.prec_nb + n_size;
		while (size++ < (inf.form_dot && n < 0 &&
						inf.prec_dot >= n_size ? -1 : 0))
			ret += write(1, " ", 1);
	}
	return (ret);
}

int	write_int_zero(t_inf inf)
{
	int	ret;

	ret = 0;
	if (inf.form_zero && !inf.form_dot)
		while (inf.prec_zero-- > 1)
			ret += write(1, "0", 1);
	else
		ret += int_write_preflag(inf, inf.form_dot ? 0 : 1, 0);
	if (!inf.form_dot)
		ret += ft_put_lint(0, inf);
	ret += int_write_postflag(inf, (inf.form_dot && !inf.prec_dot ? 0 : 1), 0);
	return (ret);
}
