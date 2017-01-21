#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char *format = "hello\n%10.4lli\nworld\n";
	int val;

	val = ft_printf(format, 42);

	printf("&&&&&&&&&&&&&&&&&&&&&\n");

	val = printf(format, 42);
	printf("val:%d\n", val);

	return (0);
}
