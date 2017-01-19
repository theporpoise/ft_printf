# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/12 11:00:36 by mgould            #+#    #+#              #
#    Updated: 2017/01/19 13:02:39 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test.out

LIBA = libft/libft.a

OBJS =  main.o ft_printf.o g_const_vars.o ft_start_strstr.o

CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

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
	gcc $(CFLAGS) -c -I . -I libft -o $@ $<

.PHONY: clean re fclean
