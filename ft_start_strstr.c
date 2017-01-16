/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_strstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:41:03 by mgould            #+#    #+#             */
/*   Updated: 2017/01/16 11:45:40 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <printf.h>

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
