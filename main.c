#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char *format = "love\n%%%#2.2lld\nworld\n";
	int val;

	val = ft_printf(format, 123);
	printf("val:%d\n", val);

	printf("&&&&&&&&&&&&&&&&&&&&&\n");

	val = printf(format, 123);
	printf("val:%d\n", val);

	return (0);
}
