/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <rmouduri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:26:36 by romain            #+#    #+#             */
/*   Updated: 2020/12/08 15:27:03 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ft_printf_H
# define ft_printf_H

# include <stdarg.h>

typedef struct	s_arginfos {
	char	conversion;
	int		prec_dot;
	int		prec_nb;
	int		prec_zero;
	int		form_dot;
	int		form_nb;
	int		form_zero;
	int		form_hash;
}				t_inf;

int				ft_printf(const char *s, ...);
t_inf			get_infos(const char *s, va_list val);
int				is_conversion(char c);
int				int_conversions(t_inf inf, va_list val);
int				uint_conversions(t_inf inf, va_list val);
int				ft_putchar_ret(char c);
int				ft_putstr_ret(t_inf inf, char *s, int to_write);
int				char_conversions(t_inf inf, va_list val);
int				int_write_postflag(t_inf inf, int nb_size, int n);
int				int_write_preflag(t_inf inf, int nb_size, int n);
int				ft_put_uint_base(unsigned int n, int base, char conv);
int				ft_put_lint(int n, t_inf inf);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ptr_conversions(t_inf inf, va_list val);
int				ft_putstr_null(t_inf inf, int to_write);
int				ft_putstr_empty(t_inf inf);
int				write_int_zero(t_inf inf);
int				write_zero_flag(t_inf inf, int nb_size, int n);
int				percent_conversion(t_inf inf);
int				nb_incr(const char *s, int i, t_inf *inf);
int				dot_incr(const char *s, int i, t_inf *inf);
int				minus_incr(const char *s, int i, t_inf *inf);
int				zero_incr(const char *s, int i, t_inf *inf);
int				write_hash(t_inf inf);

#endif
