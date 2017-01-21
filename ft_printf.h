
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>
# include <stdint.h>

typedef struct		s_box
{
	int				pound_flag;
	int				zero_flag;
	int 			minus_flag;
	int				space_flag;
	int				plus_flag;
	int				field_width;
	int				precision;
	int				len_modifier;
	int				len_value;
	char			specifier;
}					t_box;

t_box				*box_init(t_box *box);
int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);
int					matches_any_char(const char *string, char char_to_match);
int					matches_any_array(const char **string, \
					const char *str_to_match, t_box *box);
void				flags_match(const char **format, t_box *box);
void				field_width(const char **format, t_box *box);
void				precision(const char **format, t_box *box);
void				length_modifier(const char **format, t_box *box);
void				ft_put_big_nbr(intmax_t n);
char				*ft_big_itoa(intmax_t n);

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
