# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/12 11:00:36 by mgould            #+#    #+#              #
#    Updated: 2017/01/24 18:59:00 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBA = libft/libft.a

OBJS =  ft_printf.o g_const_vars.o parse_sub_helpers.o \
		parse_helpers.o ft_put_big_nbr.o ft_big_itoa.o

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBA) $(OBJS)
	ar r $(NAME) $(OBJS) $(LIBA)

$(OBJS): ft_printf.h

$(LIBA):
	cd libft/ && make

clean:
	rm -f $(OBJS)
	cd libft && make fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<
#	gcc $(CFLAGS) -c -I . libft/libft.h -o $@ $<

.PHONY: clean re fclean
