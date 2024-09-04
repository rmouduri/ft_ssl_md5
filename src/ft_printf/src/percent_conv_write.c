/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_conv_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <rmouduri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:30:37 by romain            #+#    #+#             */
/*   Updated: 2020/12/04 03:27:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

int	percent_conversion(t_inf inf)
{
	int	ret;

	ret = 0;
	if (inf.form_zero)
		while (inf.prec_zero-- > 1)
			ret += write(1, "0", 1);
	else if (inf.form_nb && inf.prec_nb > 0)
		while (inf.prec_nb-- > 1)
			ret += write(1, " ", 1);
	ret += write(1, "%", 1);
	if (inf.form_nb && inf.prec_nb < 0)
		while (inf.prec_nb++ < -1)
			ret += write(1, " ", 1);
	return (ret);
}
