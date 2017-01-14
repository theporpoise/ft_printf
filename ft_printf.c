/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/14 09:16:55 by mgould           ###   ########.fr       */
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

//FIRST VERSION BY SUNDAY EVENING
//WORKING VERSION FOR TESTING MONDAY
//TESTING VERSION BY WEDNESDAY
//SUBMIT THURSDAY
//GRADE FRIDAY


int	ft_printf(const char *format, ...)
{
	int num;
	va_list param_list;

	num = 0;
	va_start(param_list, format);

	while(*format != '\0')
	{
		ft_putchar(*format);
		format++;
	}


	va_end(param_list);
	num = printf("currently do not have counter set up\n");
	return (num);

}
