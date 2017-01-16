
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>

int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);

typedef struct		s_specifier
{
	char			*flags;
	int				field_width;
	int				precision;
	char			*len_modifier;
}					t_specifier;

/*
** extern variables
*/

extern const char	*len_mod[];

#endif
