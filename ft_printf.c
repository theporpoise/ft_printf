/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/20 16:22:25 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <limits.h>
#include <stddef.h>

//INT_MAX
//%[flags][width][.precision][length]specifier

void	move_past_specifier(const char **format, t_box *box)
{
	*format += 1;
	if (**format == '%')
	{
		*format += 1;
		ft_putchar('%');
		return ;
	}
	flags_match(format, box);
	field_width(format, box);
	precision(format, box);
	length_modifier(format, box);
	if ((matches_any_char(g_specifier, **format)))
	{
		box->specifier = **format;
		*format += 1;
	}
}

void	d_i_type_mod(t_box *box, intmax_t *storage)
{
	intmax_t cast;

	if (box->len_modifier == 0)
		*storage = (signed char)(*storage);
	else if (box->len_modifier == 1)
		*storage = (short)(*storage);
	else if (box->len_modifier == 2)
		*storage = (long long)(*storage);
	else if (box->len_modifier == 3)
		*storage = (long)(*storage);
	else if (box->len_modifier == 4)
		*storage = (intmax_t)(*storage);
	else if (box->len_modifier == 5)
		*storage = (ptrdiff_t)(*storage);
	else if (box->len_modifier == 6)
		*storage = (size_t)(*storage);
}

void	print_spec(t_box *box, va_list *param_list)
{
	char c;
	intmax_t storage;
	char *value;

	c = box->specifier;

	//this is the is a number function.
	if (c == 'd' || c == 'i')
	{
		storage = (va_arg(*param_list, intmax_t));
		d_i_type_mod(box, &storage);
		value = ft_itoa(storage);
		ft_putstr(value);
		//ft_putnbr(storage);
	}


		//storage = (long long)storage;
}


int	ft_printf(const char *format, ...)
{
	int 				len_value;
	va_list 			param_list;
	t_box				*box;

	va_start(param_list, format);
	if (!(box = box_init(box)))
		return (0);

	len_value = 0;
	while(*format != '\0')
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			len_value++;
			format++;
		}
		else if (*format == '%' && *(format + 1) == '%')
		{
			ft_putchar('%');
			format += 2;
		}
		else
		{
			move_past_specifier(&format, box);
			print_spec(box, &param_list);
		}
	}

	//DEBUG CODE
	print_struct_data(box);
	printf("ft_printf return value:%d\n", len_value);
	//END DEBUG CODE
	free(box);
	va_end(param_list);
	return (len_value);

}
























