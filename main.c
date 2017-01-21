#include <stdio.h>
#include "ft_printf.h"

int main()
{

	char *format = "hello\none:%.d\ntwo:%.d\nworld\n";
	int val;

	val = 0;
	val = ft_printf(format, 42, -1234567890123);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format, 42, -1234567890123);
	printf("val:%d\n", val);

	//convert to float for it to work
	//printf("\n%d\n", 42.42);

	//DEBUG FUNCTIONS
	//debug_d_i_ints();
	//debug_d_i_len_mod();

	return (0);
}
