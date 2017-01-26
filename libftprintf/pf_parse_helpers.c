/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:29:48 by mgould            #+#    #+#             */
/*   Updated: 2017/01/26 11:37:42 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DEBUG, RM LATER
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>

t_box	*box_init()
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
	new->len_value = 0;
	return (new);
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
		//this is NOT how the man specifies it, but is how printf works.
		if (**format == '-')
		{
			box->minus_flag = 1;
			*format += 1;
		}
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

