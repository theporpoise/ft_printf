/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/13 11:04:08 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end

//%[flags][width][.precision][length]specifier

//create ft_put_anything which puts a number or a char. . .

//0 or more flags
//optional min field width
//optional precision
//optional length modifier


int	ft_printf(const char *format, ...)
{
	int num;
	va_list param_list;


	if (!format)
		return (0);
	num = 0;
	va_start(param_list, format);

	while(num < 2)
	{
		printf("%s", va_arg(param_list, char*));
		num++;
	}

	va_end(param_list);
	num = printf("currently do not have counter set up\n");
	return (num);

}
