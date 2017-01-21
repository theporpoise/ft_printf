#include <stdio.h>
#include "ft_printf.h"

int main()
{
	char *format = "hello\none:%10lld\ntwo:%10lld\nworld\n";
	int val;

	val = ft_printf(format, 42, -1234567890123);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, 42, -1234567890123);
	printf("val:%d\n", val);

	printf("\n");

	val = ft_printf(format, 42, 12345);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, 42, 12345);
	printf("val:%d\n", val);

	printf("\n");

	val = ft_printf(format, -1, 1);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, -1, 1);
	printf("val:%d\n", val);

	printf("\n");

	val = ft_printf(format, 0, 1);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, 0, 1);
	printf("val:%d\n", val);

	printf("\n");

	val = ft_printf(format, -0, 1);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, -0, 1);
	printf("val:%d\n", val);
	printf("&&&&&&&&&&&&&&\n");
	//printf("%s", ft_big_itoa(1234567890123));


	val = printf(format, -42, 12345);

	//wow, casts it as a long so it look like a big number,
	//i'm right by accident / design
	printf("%10lld\n", -42);

	return (0);
}
