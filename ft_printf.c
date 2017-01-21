/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/21 08:40:52 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h> // va_list, func va_start, va_arg, va_end
#include <libft.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

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

intmax_t	d_i_type_mod(t_box *box, intmax_t storage)
{
	intmax_t cast;

	if (box->len_modifier == 0)
		cast = (signed char)(storage);
	else if (box->len_modifier == 1)
		cast = (short)(storage);
	else if (box->len_modifier == 2)
		cast = (long long)(storage);
	else if (box->len_modifier == 3)
		cast = (long)(storage);
	else if (box->len_modifier == 4)
		cast = (intmax_t)(storage);
	else if (box->len_modifier == 5)
		cast = (ptrdiff_t)(storage);
	else if (box->len_modifier == 6)
		cast = (size_t)(storage);

	return (cast);
}

char	*the_good_size(t_box *box, char *value)
{
	int i;
	int j;
	char *giver;

	i = 0;
	j = 0;
	if ((i = ((box->field_width) - ft_strlen(value))) > 0)
	{
		giver = (char *)malloc(sizeof(char) * (1 + box->field_width));
		while (j < i)
		{
			giver[j] = ' ';
			j++;
		}
		while (*value)
		{
			giver[j] = *value;
			j++;
			value++;
		}
		giver[j] = '\0';
		return (giver);
	}
	return (value);
}

int	print_spec(t_box *box, va_list *param_list)
{
	char c;
	intmax_t storage;
	char *value;

	c = box->specifier;

	//this is the is a number function.
	if (c == 'd' || c == 'i')
	{
		storage = d_i_type_mod(box, (va_arg(*param_list, intmax_t)));
		//value = ft_big_itoa(storage);
		value = the_good_size(box, ft_big_itoa(storage));
	}

	//after all the formatting, simply print the string
	ft_putstr(value);

	return (ft_strlen(value));
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
			len_value += print_spec(box, &param_list);
		}
	}

	//DEBUG CODE
	//print_struct_data(box);
	printf("val:%d\n", len_value);
	//END DEBUG CODE
	free(box);
	va_end(param_list);
	return (len_value);

}
























