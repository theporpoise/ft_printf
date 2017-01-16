/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/14 19:48:24 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>
#include <stdlib.h>

//%[flags][width][.precision][length]specifier

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

int		specification_pu(const char **format)
{
	int count;
	char *flags = 		"-+ #0";
	char *field_width =	"0123456789";
	char *precision =	".";
	char *len_modify =	"0123456789";
	char *specifier = 	"sSpdDioOuUxXcC";


	// count says how much to increment format
	count = 1;

	printf("specification_pu is happenning!\n");

	*format += count;

	return (count);
}

int		specifier_size(const char *format)
{
	int len;
	char *flags = 		"-+ #0";
	char *little;

	len = 1;
	little = strndup(format, 1);
	if (*format == '%')
	{
		ft_putchar('%');
		len++;
		return (len);
	}
	if (ft_strstr(flags, little))
	{
		printf("flag found\n");
		len++;
		format++;
	}
	while (ft_isdigit(*format))
	{
		len++;
		format++;
	}

	free(little);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int len_value;
	int tmp;
	va_list param_list;

	va_start(param_list, format);

	len_value = 0;
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
			tmp = specifier_size(format + 1);
			len_value += tmp;
			len_value--;
			format += tmp;
			//get_that_type
			//get_that_outpu
			//print_that_output
			//printf(get_that_output, get_that_type);
		}
		tmp = 0;
	}


	va_end(param_list);
	return (len_value);

}
























