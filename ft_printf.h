
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>

int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);

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
** single flags for last 4
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
