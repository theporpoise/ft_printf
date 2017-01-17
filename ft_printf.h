
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>

int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);

typedef struct		s_box
{
	char			*flags;
	int				field_width;
	int				precision;
	char			*len_modifier;
	char			specifier;
}					t_box;

/*
** extern variables
*/

extern const char	*len_mod[];

#endif
