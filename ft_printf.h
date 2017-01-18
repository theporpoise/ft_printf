
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>

int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);

typedef struct		s_box
{
/*
** flags
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
}					t_box;

/*
** extern variables
*/

extern const char	*len_mod[];

#endif
