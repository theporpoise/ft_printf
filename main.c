/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:11 by mgould            #+#    #+#             */
/*   Updated: 2017/01/12 11:48:30 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.c"

//get it to call correctly. DONE.
//print out all the params passed to it using the special var with print f
//get it to print all params without printf
//create subparse function and get it to substitute for string and for number
//create cut function to parse and print each section of printf

int ft_printf(const char *str, ...);

int main()
{
	char *str = "%s:%d\n";
	int val;


	val = ft_printf(str, "hello world\n", 42);
	printf(str, "tout le mond", 42);
	printf("val:%d", val);
	return (0);
}

//check the return value for printf b/c it is weird
//this project is test driven.

