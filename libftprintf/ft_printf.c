/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/28 08:00:29 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// REMOVE STDIO AFTER DEBUG
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

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
		giver = (char *)ft_memalloc(1 + min);
		while (j < i)
		{
			giver[j] = ' ';
			j++;
		}
		giver[j] = '\0';
		ft_strcat(giver, value);
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

int	digit_counter(char *str)
{
	int i;
	int num_digits;

	i = 0;
	num_digits = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num_digits++;
		i++;
	}
	return (num_digits);
}

void	precision_handler(t_box *box, char **value)
{
	int		num_digits;
	int		str_len;
	int		minus_flag;

	minus_flag = 0;
	num_digits = digit_counter(*value);
	str_len = ft_strlen(*value);
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

char	*flag_handler(t_box *box, char *value, intmax_t storage)
{
	int i;

	i = -1;
	if (box->minus_flag > 0)
		left_align_number(value);
	else if ((box->zero_flag) > 0)
		zero_flag_handler(value);
	if (storage == 0 && box->precision == 0)
		while (value[++i])
			value[i] = ' ';
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
	return (value);
}

intmax_t	ouxX_type_mod(t_box *box, intmax_t storage)
{
	intmax_t cast;

	cast = 0;
	if (box->len_modifier == -1)
		cast = (unsigned int)storage;
	else if (box->len_modifier == 0)
		cast = (unsigned char)(storage);
	else if (box->len_modifier == 1)
		cast = (unsigned short)(storage);
	else if (box->len_modifier == 2)
		cast = (unsigned long long)(storage);
	else if (box->len_modifier == 3)
		cast = (unsigned long)(storage);
	else if (box->len_modifier == 4)
		cast = (uintmax_t)(storage);
	else if (box->len_modifier == 5)
		cast = (ptrdiff_t)(storage);
	else if (box->len_modifier == 6)
		cast = (size_t)(storage);

	return (cast);
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
	if (c == 'd' || c == 'i')
	{
		storage = d_i_type_mod(box, (va_arg(*param_list, intmax_t)));
		value = field_width_handler(box, pf_big_itoa_base(storage, 10));
		precision_handler(box, &value);
		value = flag_handler(box, value, storage);
	}
	else if (c == 'o')
	{
		storage = ouxX_type_mod(box, (va_arg(*param_list, intmax_t)));
		value = field_width_handler(box, pf_big_itoa_base(storage, 8));
		//i believe my handlers look for is_digit, so will have error with
		//base > 10
		precision_handler(box, &value);
		value = flag_handler(box, value, storage);
	}
	ft_putstr(value);
	return (value == NULL ? 0 : ft_strlen(value));
}

int	move_past_specifier(const char **format, t_box *box, int *len_value)
{
	//may fix parse read by removing if else and adding
	//while *format += 1 run all functions
 	if (**format != '%')
	{
		ft_putchar(**format);
		*len_value += 1;
		*format += 1;
		return (0);
	}
	else if (**format == '%' && *((*format + 1)) == '%')
	{
		ft_putchar('%');
		*len_value += 1;
		*format += 2;
		return (0);
	}
	*format += 1;
	flags_match(format, box);
	field_width(format, box);
	precision(format, box);
	length_modifier(format, box);
	if ((matches_any_char(g_specifier, **format)))
	{
		box->specifier = **format;
		//possible error if specifier is len 2, doesn't skip 2
		*format += 1;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int 				len_value;
	va_list 			param_list;
	t_box				*box;

	va_start(param_list, format);
	if (!(box = box_init()))
		return (0);

	len_value = 0;
	while(*format != '\0')
	{
		if (move_past_specifier(&format, box, &len_value))
			len_value += print_spec(box, &param_list);
	}
	//DEBUG CODE
	//debug_print_struct_data(box);
	//END DEBUG CODE
	free(box);
	va_end(param_list);
	return (len_value);
}





