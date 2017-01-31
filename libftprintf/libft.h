/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgould <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:38:24 by mgould            #+#    #+#             */
/*   Updated: 2017/01/30 09:20:50 by mgould           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdint.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_box
{
	int				pound_flag;
	int				zero_flag;
	int				minus_flag;
	int				space_flag;
	int				plus_flag;
	int				field_width;
	int				precision;
	int				len_modifier;
	int				len_value;
	char			specifier;
}					t_box;

t_box				*box_init();
int					ft_printf(const char *str, ...);
char				*ft_start_strstr(const char *big, const char *little);
int					matches_any_char(const char *string, char char_to_match);
int					matches_any_array(const char **str, \
					const char *to_match, t_box *box);
void				flags_match(const char **format, t_box *box);
void				field_width(const char **format, t_box *box);
void				precision(const char **format, t_box *box);
void				length_modifier(const char **format, t_box *box);
void				pf_put_big_nbr(intmax_t n);
char				*pf_big_itoa(intmax_t n);
char				*pf_big_itoa_base(intmax_t n, int base);
char				*pf_ubig_itoa_base(uintmax_t n, int base);

/*
** extern variables
*/

extern const char	*g_len_mod[];
extern const char	*g_specifier;
extern const char	*g_flags;

// debug function DELETE THIS LATER
void				debug_print_struct_data(t_box *box);
void				debug_d_i_ints();
void				debug_d_i_len_mod();
void				debug_d_i_precision();
void				debug_d_i_space();
void				debug_d_i_plus();
void				debug_d_i_pound();
// debug functions delete this late and remove functions

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little, \
					size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_wc(char *s, char c);
char				*ft_make_word(char *s, char c);
void				ft_mnbr(char *num, int len, int n);
char				*ft_getz(char *num);
void				*ft_fill_char(char *value, char *s, int len, int i);
int					ft_recursive_factorial(int nb);
int					ft_iterative_power(int nb, int power);
int					ft_sqrt(int nb);
int					ft_is_prime(int nb);
#endif
