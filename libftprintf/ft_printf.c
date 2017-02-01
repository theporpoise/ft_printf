/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/01/31 16:03:29 by mgould           ###   ########.fr       */
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


char	*ft_strstick(char *prepend, char *original, int index)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = index;
	new = ft_strnew(ft_strlen(original + index) + ft_strlen(prepend));
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
	free(original);
	return (new);
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

	i = ((value == NULL) ? 0 : ft_strlen(value));
	j = 0;
	min = ((box->precision > box->field_width) ? box->precision : box->field_width);
	if ((i = (min - i)) > 0)
	{
		giver = (char *)ft_memalloc(1 + min);
		while (j < i)
		{
			giver[j] = ' ';
			j++;
		}
		giver[j] = '\0';
		if (value)
			ft_strcat(giver, value);
		free(value);
		return (giver);
	}
	return (value);
}



int	digit_counter(char *str)
{
	//may need to add ability to count alphanumeric for hexadecimal
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

	if (*value == NULL)
		return ;
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
		*value = ft_strstick("-", *value, 0);
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

void	left_align_octal(char *value)
{
	int count;
	int str_len;
	int i;

	i = 0;
	count = 0;
	str_len = ft_strlen(value);
	while (value[count] == ' ')
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
		value = ft_strstick("+", value, 0);
	else if (box->plus_flag > 0)
	{
		i = 0;
		while (value[i] == ' ')
			i++;
		if (!(value[i] == '-'))
			value[i - 1] = '+';
	}
	else if (box->space_flag > 0 && ft_isdigit(*value))
		value = ft_strstick(" ", value, 0);
	return (value);
}

intmax_t	ouxX_type_mod(t_box *box, uintmax_t storage)
{
	uintmax_t cast;

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

void	str_toupper(char *value)
{
	while (*value)
	{
		*value = ft_toupper(*value);
		value++;
	}
}


char	*oxX_flag_handler(t_box *box, char *value)
{
	char *new;
	int i;

	i = 0;
	new = value;
	//
	if (box->minus_flag > 0 && box->pound_flag < 0)
		left_align_number(new);
	else if (box->minus_flag > 0)
		left_align_octal(new);
	else if ((box->zero_flag) > 0)
		zero_flag_handler(new);
	if (box->pound_flag > 0)
	{
		if (new[1] != 'x' && new[0] == '0')
		{
			while(new[i] != 'x')
				i++;
			new[i] = '0';
			new[1] = 'x';
		}
	}

	return (new != NULL ? new : value);
}


void	str_precision_handler(t_box *box, char **value)
{
	int		num_digits;
	int		str_len;
	int		minus_flag;

	if (*value == NULL)
		return ;
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
		*value = ft_strstick("-", *value, 0);
	else if (minus_flag)
	{
		while (!(ft_isdigit(**value)))
			*value += 1;
		**value = '-';
	}
}

char	*percent_printer(char *value, t_box *box)
{

	value = field_width_handler(box, value);
	precision_handler(box, &value);
	if (value == NULL)
	{
		value = ft_strnew(1);
		value[0] = '%';
	}
	else
		value[ft_strlen(value) - 1] = '%';
	value = flag_handler(box, value, 1);

	return (value);
}

char	*d_i_printer(char *value, t_box *box, va_list *param_list)
{
	intmax_t	storage;

	storage = d_i_type_mod(box, (va_arg(*param_list, intmax_t)));
	value = field_width_handler(box, pf_big_itoa_base(storage, 10));
	precision_handler(box, &value);
	value = flag_handler(box, value, storage);

	return (value);
}

char	*o_printer(char *value, t_box *box, va_list *param_list)
{
	uintmax_t	ustorage;

	ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
	value = field_width_handler(box, pf_ubig_itoa_base(ustorage, 8));
	precision_handler(box, &value);
	value = flag_handler(box, value, ustorage);

	return (value);
}

char	*x_printer(char *value, t_box *box, va_list *param_list)
{
	uintmax_t	ustorage;

	ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
	if (ustorage != 0)
		value = pf_ubig_itoa_base(ustorage, 16);
	else if (ustorage == 0 && box->precision == 0 && box->field_width < 1)
		return (NULL);
	else if (ustorage == 0 && box->precision == -1)
	{
		value = ft_getz(value);
		return (value);
	}
	else
		value = ft_strnew(0);
	if (box->pound_flag > 0 && ustorage != 0)
		value = ft_strstick("0x", value, 0);
	value = field_width_handler(box, value);
	precision_handler(box, &value);
	value = oxX_flag_handler(box, value);
	if (box->specifier == 'X')
		str_toupper(value);

	return (value);
}



int		print_spec(t_box *box, va_list *param_list)
{
	char c;
	char *value;
	int i;

	i = 0;
	c = box->specifier;
	value = NULL;
	if (box->specifier == '%')
	{
		value = percent_printer(value, box);
	}
	else if (c == 'd' || c == 'i')
	{
		value = d_i_printer(value, box, param_list);
	}
	else if (c == 'o')
	{
		value = o_printer(value, box, param_list);
	}
	else if (c == 'x' || c == 'X')
	{
		value = x_printer(value, box, param_list);
		/*
		ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
		if (ustorage != 0)
			value = pf_ubig_itoa_base(ustorage, 16);
		else if (ustorage == 0 && box->precision == 0 && box->field_width < 1)
			return (0);
		else if (ustorage == 0 && box->precision == -1)
		{
			value = ft_getz(value);
			ft_putstr(value);
			return (ft_strlen(value));
		}
		else
			value = ft_strnew(0);

		if (box->pound_flag > 0 && ustorage != 0)
			value = ft_strstick("0x", value, 0);
		value = field_width_handler(box, value);
		precision_handler(box, &value);
		value = oxX_flag_handler(box, value);
		if (c == 'X')
			str_toupper(value);
		*/
	}
	else if (c == 's')
	{
		value = va_arg(*param_list, char *);
		//precision handler, get right # chars
		//field width handler, get right size
		//left align handler
	}


	ft_putstr(value);
	return (value == NULL ? 0 : ft_strlen(value));
}

int	move_past_specifier(const char **format, t_box *box, int *len_value)
{
	if (**format != '%')
	{
		ft_putchar(**format);
		*len_value += 1;
		*format += 1;
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





