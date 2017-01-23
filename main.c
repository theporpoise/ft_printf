#include <stdio.h>
#include "ft_printf.h"

int main()
{
/*
	char *format0 = "one:% 10d\ntwo:% 10d\n";
	int val;

	val = 0;
	val = ft_printf(format0, 42, 1234567890123);
	printf("val:%d\n", val);
	printf("&&&&&&&&&&&&&&&&&&&&&\n");
	val = printf(format0, 42, 1234567890123);
	printf("val:%d\n", val);
*/
	printf("DEBUG FUNCTION CALLS\n");
	//convert to float for it to work
	//printf("\n%d\n", 42.42);

	//DEBUG FUNCTIONS
	debug_d_i_ints();
	//debug_d_i_len_mod();
	//debug_d_i_precision();
	//debug_d_i_space();
	//debug_d_i_plus();

	return (0);
}
