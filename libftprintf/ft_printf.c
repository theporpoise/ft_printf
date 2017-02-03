/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:57 by mgould            #+#    #+#             */
/*   Updated: 2017/02/03 09:39:51 by mgould           ###   ########.fr       */
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
#include <stddef.h>
#include <wchar.h>


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



char	*x_printer(char *value, t_box *box, va_list *param_list)
{
	uintmax_t	ustorage;

	ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
	if (ustorage != 0)
		value = pf_ubig_itoa_base(ustorage, 16);
	else if (ustorage == 0 && box->precision == 0 && box->field_width < 1)
		return (ft_strnew(0));
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

char	*pf_strnewchar(size_t size, char any)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	while (i < size)
	{
		str[i] = any;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*str_precision_handler(t_box *box, char *value)
{
	int		str_len;
	char	*ret;

	if (value == NULL || box->precision < 0)
	{
		return value;
	}
	str_len = ft_strlen(value);
	ret = ft_strdup(value);
	if (str_len > box->precision)
		ret[box->precision] = '\0';

	return (ret);
}

char	*str_field_width_handler(t_box *box, char *value)
{
	int 	i;
	int 	j;
	char 	*giver;
	int		min;

	i = ((value == NULL) ? 0 : ft_strlen(value));
	j = 0;
	min = box->field_width;

	if ((i = (min - i)) > 0)
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

void	left_align_str(char *value)
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

char	*str_printer(t_box *box, va_list *param_list, char *value)
{

	value = va_arg(*param_list, char *);

	if (value == NULL)
		return (value);
	else
	{
		value = str_precision_handler(box, value);
		value = str_field_width_handler(box, value);
		if (box->minus_flag > 0)
			left_align_str(value);
	}

	return (value);
}

char	*char_field_width_handler(t_box *box, char *value)
{
	int 	i;
	int 	j;
	char 	*giver;
	int		min;

	i = ((value == NULL) ? 0 : ft_strlen(value));
	if (i == 0)
		i++;
	j = 0;
	min = box->field_width;

	if ((i = (min - i)) > 0)
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

char	*c_printer(t_box *box, va_list *param_list, char *value, int *print_len)
{
	value = ft_strnew(1);
	//ft_putstr("you are in c_printer");
	value[0] = (char)(wint_t)va_arg(*param_list, wint_t);
	if (value[0] == '\0')
		*print_len += 1;
	value = char_field_width_handler(box, value);
	if (box->minus_flag > 0)
		left_align_str(value);

	return (value);
}

char	*o_precision_handler(t_box *box, char **value)
{
	int		str_len;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	str_len = 0;
	if (*value == NULL)
		return (*value);
	else if (box->precision > (str_len = ft_strlen(*value)))
	{
		new = ft_strnew(box->precision - str_len);
		ft_memset((void *)new, '0', (box->precision - str_len));
		new = ft_strjoin(new, *value);
	}
	else
		return (*value);
	return (new);
}

char	*o_pound_handler(char *value, t_box *box, uintmax_t ustorage)
{
	int i;

	i = 0;
	if (box->pound_flag > 0 && value[i] == ' ')
	{
		while (value[i] == ' ')
			i++;
		value[i - 1] = '0';
		return (value);
	}
	else if (box->pound_flag > 0 && value[i] != ' ' &&
			(ustorage != 0 || box->precision > -1))
		return (ft_strjoin("0", value));

	return (value);
}

char	*o_printer(char *value, t_box *box, va_list *param_list)
{
	uintmax_t	ustorage;

	ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
	if (ustorage == 0 && box->precision == 0)
		value = ft_strnew(0);
	else if (ustorage == 0)
		value = ft_getz(value);
	else
		value = pf_ubig_itoa_base(ustorage, 8);
	value = o_precision_handler(box, &value);
	value = str_field_width_handler(box, value);
	value = o_pound_handler(value, box, ustorage);
	if (box->minus_flag > 0)
		left_align_octal(value);
	if (box->zero_flag > 0)
		zero_flag_handler(value);
	return (value);
}


char	*u_printer(t_box *box, va_list *param_list, char *value)
{
	uintmax_t	ustorage;

	ustorage = ouxX_type_mod(box, (va_arg(*param_list, uintmax_t)));
	value = pf_ubig_itoa_base(ustorage, 10);
	value = o_precision_handler(box, &value);
	value = str_field_width_handler(box, value);
	if (box->minus_flag > 0)
		left_align_octal(value);
	if (box->zero_flag > 0)
		zero_flag_handler(value);

	return (value);
}

void	specifier_update(t_box *box)
{
	if (box->specifier == 'D' || box->specifier == 'O' || box->specifier == 'U' \
			|| box->specifier == 'C' || box->specifier == 'S')
	{
		box->len_modifier = 3;
		box->specifier = ft_tolower(box->specifier);
	}
	if (box->specifier == 'p')
	{
		box->pound_flag = 1;
		box->len_modifier = '3';
	}


}

char	*d_i_precision_handler(t_box *box, char **value, intmax_t storage)
{
	int		num_digits;
	int		str_len;
	int		minus_flag;
	char	*new;

	new = NULL;
	if (*value == NULL)
		return *value;
	minus_flag = 0;
	num_digits = digit_counter(*value);
	str_len = ft_strlen(*value);
	if (box->precision == 0 && storage == 0)
	{
		new = ft_strnew(0);
		return (new);
	}
	if (box->precision > num_digits)
	{
		new = ft_strnew(box->precision - num_digits);
		ft_memset(new, '0', (box->precision - num_digits));
		new = ft_strjoin(new, *value);

		return (new);
	}

	return (*value);
}

char	*d_i_flag_handler(t_box *box, char *value, intmax_t storage)
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
			value = ft_strstick("+", value, i);
	}
	else if (box->space_flag > 0 && ft_isdigit(*value))
		value = ft_strstick(" ", value, 0);
	return (value);
}

//type, itoa, precision, zero (ignored precision), space, plus, minus, width

int		digit_count(char *value)
{
	int count;

	count = 0;
	while(*value)
	{
		if (ft_isdigit(*value))
			count++;
		value++;
	}
	return (count);
}

char	*d_i_space_plus_handler(t_box *box, char *value, intmax_t storage)
{
	int i;

	i = 0;
	if (box->space_flag > 0 && storage != 0)
	{
		if (*value == '0' && digit_count(value) > box->precision)
			*value = ' ';
		if (*value != ' ' && *value != '-')
		{
			value = ft_strjoin(" ", value);
		}
	}
	if (box->plus_flag > 0 && storage >= 0)
	{
		if ((*value == '0') && storage == 0)
			value = ft_strjoin("+", value);
		else if ((*value == '0' && digit_count(value) > box->precision))
			*value = '+';
		else if (*value == ' ')
		{
			while(value[i] == ' ')
				i++;
			value[i - 1] = '+';
		}
		else
			value = ft_strjoin("+", value);
	}
	return (value);
}

char *d_i_negative_handler(char *value, intmax_t storage)
{
	int i;

	i = 0;
	if (storage < 0 && *value != '-')
	{
		while(value[i])
		{
			if (value[i] == '-')
				value[i] = '0';
			i++;
		}
		i = 0;
		while(value[i] == ' ')
			i++;
		if (value[i] == '0' || value[i] == '-')
			value[i] = '-';
		else
			value[i - 1] = '-';
	}
	return (value);
}

void	d_i_zero_flag_handler(t_box *box, char *value)
{
	int i;

	if (box->precision > -1)
		return ;
	i = 0;
	while (value[i] == ' ')
	{
		value[i] = '0';
		i++;
	}
}

uintmax_t	absolute_value(intmax_t storage)
{
	uintmax_t		ret;

	ret = -(storage);
	return (ret);
}

char	*d_i_printer(char *value, t_box *box, va_list *param_list)
{
	intmax_t	storage;

	storage = d_i_type_mod(box, (va_arg(*param_list, intmax_t)));
	if (storage < 0)
		value = pf_ubig_itoa_base(absolute_value(storage), 10);
	else
		value = pf_big_itoa_base(storage, 10);
	if (storage < 0 && (ft_strchr(value, '-') == NULL))
		value = ft_strstick("-", value, 0);
	value = d_i_precision_handler(box, &value, storage);
	value = str_field_width_handler(box, value);
	if (box->minus_flag > 0)
		left_align_octal(value);
	else if (box->zero_flag > 0)
		d_i_zero_flag_handler(box, value);
	value = d_i_negative_handler(value, storage);
	value = d_i_space_plus_handler(box, value, storage);
	if (value[box->field_width] == ' ')
		value[box->field_width] = '\0';

	return (value);
}


int		print_spec(t_box *box, va_list *param_list)
{
	char	c;
	char	*value;
	int		print_len;

	print_len = 0;
	value = NULL;
	specifier_update(box);
	c = box->specifier;
	//ft_putstr("out of specifier update");
	if (box->specifier == '%')
		value = percent_printer(value, box);
	else if (c == 'd' || c == 'i')
		value = d_i_printer(value, box, param_list);
	else if (c == 'o')
		value = o_printer(value, box, param_list);
	else if (c == 'x' || c == 'X' c == 'p')
		value = x_printer(value, box, param_list);
	else if (c == 's' || c == 'S')
		value = str_printer(box, param_list, value);
	else if (c == 'c')
		value = c_printer(box, param_list, value, &print_len);
	else if (c == 'u' || c == 'U')
		value = u_printer(box, param_list, value);
	else if (c == 'p')
		value = NULL;

	if (value == NULL)
	{
		ft_putstr("(null)");
		print_len += 6;
	}
	else
	{
		ft_putstr(value);
		print_len += ft_strlen(value);
	}
	return (print_len);
	//return (value == NULL ? 0 : print_len);
}

// wctmb, wcstmbs man these

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
		{
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





