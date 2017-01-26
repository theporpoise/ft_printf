/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:23:06 by mgould            #+#    #+#             */
/*   Updated: 2017/01/26 11:38:02 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_start_strstr(const char *big, const char *little)
{
	size_t	j;
	char	*ptr;

	j = 0;
	ptr = (char *)big;
	if (!(little[j]) && !(ptr[j]))
		return (ptr);
	while ((ptr[j] == little[j]) && ptr[j])
	{
		j++;
	}
	if (!little[j])
		return (&ptr[j]);
	return (NULL);
}

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
