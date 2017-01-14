/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/14 09:57:25 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>

//%[flags][width][.precision][length]specifier

//create ft_put_anything which puts a number or a char. . .

//IN THIS ORDER
//0 or more flags
//optional min field width
/*
 * field width is over ridden by thingy size. . .
 * negative sign is simply interpreted as a - flag.
 */

//optional precision
//optional length modifier

//determine what type it is. . . so you can passs to va_arg
//fuck this jazz,  unbelieveable. what a stupid fucking moron function.

//printf - create a print up to a specifier funtion that also returns the len
//it printed. . .

int		conversion_specification_processor(const char **format)
{
	int count;
	// count says how much to increment format
	count = 1;

	printf("conversion_specification_processor is happenning!\n");

	*format += count;

	return (count);
}


int	ft_printf(const char *format, ...)
{
	int len_value;
	int tmp;
	va_list param_list;

	va_start(param_list, format);

	len_value = 1;
	tmp = 0;
	while(*format != '\0')
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			format++;
			len_value++;
		}
		else
		{
			tmp = conversion_specification_processor(&format);
			len_value += tmp;
		}
		format += tmp;
		tmp = 0;
	}


	va_end(param_list);
	return (len_value);

}
