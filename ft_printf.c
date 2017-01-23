/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/23 15:20:36 by mgould           ###   ########.fr       */
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
	//ft_putstr("you are here\n");
	field_width(format, box);
	//ft_putstr("you are here\n");
	precision(format, box);
	//ft_putstr("you are here\n");
	length_modifier(format, box);
	if ((matches_any_char(g_specifier, **format)))
	{
		box->specifier = **format;
		*format += 1;
	}
	//ft_putstr("you are here\n");
}



intmax_t	d_i_type_mod(t_box *box, intmax_t storage)
{
	intmax_t cast;

	cast = 0;
	if (box->len_modifier == -1)
		cast = (int)storage;
	else if (box->len_modifier == 0)
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

char	*field_width_handler(t_box *box, char *value)
{
	int 	i;
	int 	j;
	char 	*giver;
	int		min;

	i = 0;
	j = 0;
	min = ((box->precision > box->field_width) ? box->precision : box->field_width);
	if ((i = (min - ft_strlen(value))) > 0)
	{
		giver = (char *)malloc(sizeof(char) * (1 + min));
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

char	*ft_prestr(char *prepend, char *original)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	//ft_putstr("inside pre-string");
	new = ft_strnew(ft_strlen(original) + ft_strlen(prepend));
	while (prepend[i])
	{
		new[i] = prepend[i];
		i++;
	}
	while (original[j])
	{
		new[i] = original[j];
		j++;
		i++;
	}
	return (new);
}

void	precision_handler(t_box *box, char **value)
{
	int		num_digits;
	int		j;
	int		str_len;
	int		minus_flag;

	minus_flag = 0;
	j = 0;
	num_digits = 0;
	str_len = ft_strlen(*value);
	while ((*value)[j])
	{
		if (ft_isdigit((*value)[j]))
			num_digits++;
		j++;
	}
	while ((box->precision - num_digits) > 0)
	{
		if ((*value)[str_len - num_digits - 1] == '-')
			minus_flag = 1;
		(*value)[str_len - num_digits - 1] = '0';
		num_digits++;
	}
	if (**value == '0' && minus_flag > 0)
		*value = ft_prestr("-", *value);
	else if (minus_flag)
	{
		while (!(ft_isdigit(**value)))
			*value += 1;
		**value = '-';
	}
}

void	left_align_number(char *value)
{
	int count;
	int str_len;
	int i;

	i = 0;
	count = 0;
	str_len = ft_strlen(value);

	while (value[count] == '0' || value[count] == ' ')
		count++;
	while (value[count])
	{
		value[i] = value[count];
		count++;
		i++;
	}
	while (value[i])
	{
		value[i] = ' ';
		i++;
	}
}

void	zero_flag_handler(char *value)
{
	int i;

	i = 0;
	while (value[i] == ' ')
	{
		value[i] = '0';
		i++;
	}
}

char	*flag_handler(t_box *box, char *value)
{
	//ft_putstr("inside flag handler\n");
	if (box->minus_flag > 0)
	{
		left_align_number(value);
	}
	else if ((box->zero_flag) > 0)
	{
		zero_flag_handler(value);
	}
	return (value);
}

int		print_spec(t_box *box, va_list *param_list)
{
	char c;
	intmax_t storage;
	char *value;
	int i;

	i = 0;
	c = box->specifier;
	value = NULL;
	//d and i do NOT care about the # flag.
	if (c == 'd' || c == 'i')
	{
		storage = d_i_type_mod(box, (va_arg(*param_list, intmax_t)));
		value = field_width_handler(box, ft_big_itoa(storage));
		precision_handler(box, &value);
		value = flag_handler(box, value);
		// if precision is zero, value is zero, print empy string (nothing);
		if (storage == 0 && box->precision == 0)
			while (value[i])
			{
				value[i] = ' ';
				i++;
			}
		if (box->plus_flag > 0 && ft_isdigit(*value))
			value = ft_prestr("+", value);
		else if (box->plus_flag > 0)
		{
			i = 0;
			while (value[i] == ' ')
				i++;
			if (!(value[i] == '-'))
				value[i - 1] = '+';
		}
		else if (box->space_flag > 0 && ft_isdigit(*value))
			value = ft_prestr(" ", value);
	}
	ft_putstr(value);
	//check signed and unsigned  uintmax_tc
	return (value == NULL ? 0 : ft_strlen(value));
}


int	ft_printf(const char *format, ...)
{
	int 				len_value;
	va_list 			param_list;
	t_box				*box;

	va_start(param_list, format);
	box = NULL;
	if (!(box = box_init()))
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
	//debug_print_struct_data(box);
	//END DEBUG CODE
	free(box);
	va_end(param_list);
	return (len_value);
}





