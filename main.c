/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:14:11 by mgould            #+#    #+#             */
/*   Updated: 2017/01/14 19:48:36 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

//get it to call correctly. DONE.
//print out all the params passed to it using the special var with print f
//get it to print all params without printf
//create subparse function and get it to substitute for string and for number
//and print out corrected for this one use case
//REASSESS NEXT STEPS
//
//va_list has no idea, it will keep going forever. . .


int main()
{
	char *format = "love\n%%%0s\nstuff\n";
	int val;

	val = ft_printf(format, "hello world\n");
	printf("val:%d\n", val);

	printf("&&&&&&&&&&&&&&&&&&&&&\n");

	val = printf(format, "hello world\n");
	printf("val:%d\n", val);

	return (0);
}


/*
	char *format = "love\n%sstuff\n";
	int val;

	val = ft_printf(format, "hello world\n");
	printf("val:%d\n", val);

	val = printf(format, "hello world\n");
	printf("val:%d\n", val);

*/





//check the return value for printf b/c it is weird

/*
String, stuff in middle, number, newline"
	char *format = "%s:%d\n";
	int val;

	val = ft_printf(format, "hello world\n", 42);
	printf("val:%d\n", val);

	val = printf(format, "hello world\n", 42);
	printf("val:%d\n", val);


*/



/*
wrap this in a function in a separate file, then I can have lots of printf
testing examples to look at later.
	printf("PRINT F TESTING %\n");
	printf("\n0:");
	printf("");
	printf("\n1:");
	printf("%");
	printf("\n2:");
	printf("%%");
	printf("\n3:");
	printf("%%%");
	printf("\n4:");
	printf("%%%%");
	printf("\n5:");
	printf("%%%%%");
	printf("\n6:");
	printf("%%%%%%");
	printf("\n");

*/
