/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_str_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 11:37:15 by mgould            #+#    #+#             */
/*   Updated: 2017/02/07 12:50:13 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>

char	*str_precision_handler(t_box *box, char *value)
{
	int		str_len;
	char	*ret;

	if (value == NULL || box->precision < 0)
	{
		return (value);
	}
	str_len = ft_strlen(value);
	ret = ft_strdup(value);
	if (str_len > box->precision)
		ret[box->precision] = '\0';
	return (ret);
}

char	*str_printer(t_box *box, va_list *param_list, char *value)
{
	//value = (char *)(wchar_t *)va_arg(*param_list, wchar_t *);
	//value = (char *)(wint_t *)va_arg(*param_list, wint_t *);
	// this is failing ftprintf.com, return something other than NULL
	//if (value == NULL && box->specifier == 'S')
	//	return (value = ft_strnew(0));
	//if (value == NULL)
	//	return (value);
	if (box->specifier == 's')
	{
		value = (char *)(wchar_t *)va_arg(*param_list, wchar_t *);
		if (value == NULL)
			return (value);
		value = ft_strdup(value);
		value = str_precision_handler(box, value);
		value = str_field_width_handler(box, value);
		if (box->minus_flag > 0)
			left_align_str(value);
	}
	else if (box->specifier == 'S')
	{
		value = (char *)(wchar_t *)va_arg(*param_list, wchar_t *);
		if (value == NULL)
			return (value);
	}
	return (value);
}