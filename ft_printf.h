
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>



typedef struct		s_box
{
/*
** flags - 5 total
*/
	int				pound_flag;
	int				zero_flag;
	int 			minus_flag;
	int				space_flag;
	int				plus_flag;
/*
** field width and precision
*/
	int				field_width;
	int				precision;
	int				len_modifier;
	char			specifier;
	int				len_value;
}					t_box;

int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);

/*
** extern variables
*/

extern const char	*len_mod[];
extern const char	*g_specifier;
extern const char	*g_flags;

// debug function DELETE THIS LATER
void	print_struct_data(t_box *box);
//

#endif
