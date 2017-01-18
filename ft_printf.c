/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/18 13:30:27 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>
#include <stdlib.h>
#include <ft_printf.h>

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
//specifier

//determine what type it is. . . so you can passs to va_arg
//fuck this jazz,  unbelieveable. what a stupid fucking moron function.

//printf - create a print up to a specifier funtion that also returns the len
//it printed. . .

//old code
int		specification_pu(const char **format)
{
	char *flags = 		"-+ #0";
	char *field_width =	"0123456789";
	char *precision =	".";
	char *len_modify =	"0123456789";
	char *specifier = 	"sSpdDioOuUxXcC";

	return (0);
}

int		matches_any_char(char *string, char char_to_match)
{
	while (*string)
	{
		if (char_to_match == *string)
			return (1);
		string++;
	}
	return (0);
}

int		matches_any_array(const char **string, const char *str_to_match)
{
	while (*string)
	{
		//printf("1:%s\n", *string);
		if (ft_start_strstr(str_to_match, *string))
		{
			//printf("%c\n%c\n", *str_to_match, **string);
			return ft_strlen(*string);
		}
		string += 1;
	}
	return (0);
}



void	move_past_specifier(const char **format)
{
	char	*flags = "-+ #0";
	char 	*specifier = 	"sSpdDioOuUxXcC";
	int		len;

	len = 0;
	*format += 1;
	if (**format == '%')
	{
		*format += 1;
		ft_putchar('%');
		return ;
	}
	//flags
	while (matches_any_char(flags, **format))
	{
		printf("flag found:%c\n", **format);
		*format += 1;
	}
	//min field width
	while (ft_isdigit(**format))
	{
		printf("field width found\n");
		*format +=1;
	}
	//precision
	if (**format == '.')
	{
		printf("precision found\n");
		*format += 1;
		while (ft_isdigit(**format))
				{
					*format += 1;
				}
	}
	//length modifier
	while ((len = matches_any_array(len_mod, *format)))
	{
		printf("len is:%d\n", len);
		printf("len modifier found:%c\n", **format);
		*format += len;
	}
	//conversion specifier
	if ((matches_any_char(specifier, **format)))
	{
		printf("specifier found:%c\n", **format);
		*format += 1;
	}
	return ;
}

// not sure how to proceed with the read in.  I want to store teh result of the
// read to a struct, but not sure how best to do it.  Also, I want to pass
// this on to the result of va_whatever so I can grab the result and print it.

int	ft_printf(const char *format, ...)
{
	int 				len_value;
	va_list 			param_list;
	//extern t_box		*box;

	va_start(param_list, format);
	//if (!(box = (t_box*)malloc(sizeof(t_box))))
	//	return (0);

	len_value = 0;
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
			move_past_specifier(&format);
			//get_that_type
			//get_that_outpu
			//print_that_output
			//printf(get_that_output, get_that_type);
		}
	}

	//build a functio to fully free box, or do it before here
	//need to free box's elements, like *flags array
	//free(box);
	va_end(param_list);
	return (len_value);

}
























