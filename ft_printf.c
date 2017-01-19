/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/19 13:08:40 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <limits.h>

//INT_MAX
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

//printf - create a print up to a specifier funtion that also returns the len
//it printed. . .

int		matches_any_char(const char *string, char char_to_match)
{
	while (*string)
	{
		if (char_to_match == *string)
			return (1);
		string++;
	}
	return (0);
}

int		matches_any_array(const char **string, const char *str_to_match, t_box *box)
{
	int i;

	i = 0;
	while (*string)
	{
		if (ft_start_strstr(str_to_match, *string))
		{
			box->len_modifier = i;
			return ft_strlen(*string);
		}
		i++;
		string += 1;
	}
	return (0);
}

void	flags_match(const char **format, t_box *box)
{
	while (matches_any_char(g_flags, **format))
	{
		if (**format == '#')
			box->pound_flag = 1;
		else if (**format == '0')
			box->zero_flag = 1;
		else if (**format == '-')
			box->minus_flag = 1;
		else if (**format == ' ')
			box->space_flag = 1;
		else if (**format == '+')
			box->plus_flag = 1;
		*format += 1;
	}
}

void	field_width(const char **format, t_box *box)
{
	int value;

	value = -1;
	if (ft_isdigit(**format))
		value = 0;
	while (ft_isdigit(**format))
	{
		value *= 10;
		value += (**format - '0');
		*format += 1;
	}
	box->field_width = value;
}

void	precision(const char **format, t_box *box)
{
	int value;

	value = -1;
	if (**format == '.')
	{
		value = 0;
		*format += 1;
		while (ft_isdigit(**format))
				{
					value *= 10;
					value += (**format - '0');
					*format += 1;
				}
	}
	box->precision = value;
}

void	length_modifier(const char **format, t_box *box)
{
	int	len;

	len = 0;
	while ((len = matches_any_array(len_mod, *format, box)))
	{
		*format += len;
	}

}

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

t_box	*box_init(t_box *box)
{
	t_box	*new;

	if (!(new = (t_box*)malloc(sizeof(t_box))))
		return (NULL);
	new->pound_flag = -1;
	new->zero_flag = -1;
	new->minus_flag = -1;
	new->space_flag = -1;
	new->plus_flag = -1;

	new->field_width = -1;
	new->precision = -1;
	new->len_modifier = -1;
	new->specifier = 0;

	return (new);
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
			format++;
			len_value++;
		}
		else
		{
			move_past_specifier(&format, box);
			//get_that_type
			//get_that_outpu
			//print_that_output
			//printf(get_that_output, get_that_type);
		}
	}

	// Begin Debug Code
	printf("val:%d\n", len_value);
	printf("&&&&&&&&&&&&&\n");
	printf("pound_flag:%d\n", box->pound_flag);
	printf("zero_flag:%d\n", box->zero_flag);
	printf("minus_flag:%d\n", box->minus_flag);
	printf("space_flag:%d\n", box->space_flag);
	printf("plus_flag:%d\n", box->plus_flag);
	printf("field_width:%d\n", box->field_width);
	printf("precision:%d\n", box->precision);
	printf("len_modifier:%d\n", box->len_modifier);
	printf("specifier:%c\n", box->specifier);
	// End Debug Code

	free(box);
	va_end(param_list);
	return (len_value);

}
























