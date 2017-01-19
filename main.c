#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char *format = "love\n%%%+- #010.10lld\nworld\n";
	int val;

	val = ft_printf(format, 123);

	printf("&&&&&&&&&&&&&&&&&&&&&\n");

	val = printf(format, 123);
	printf("val:%d\n", val);

	return (0);
}
