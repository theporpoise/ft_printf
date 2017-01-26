/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_big_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 07:03:44 by mgould            #+#    #+#             */
/*   Updated: 2017/01/24 17:22:05 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <libft.h>
#include "libft/libft.h"
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
//#include <ft_printf.h>
#include "ft_printf.h"

void	ft_put_big_nbr(intmax_t n)
{
	intmax_t	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_put_big_nbr(nb / 10);
		ft_put_big_nbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}
