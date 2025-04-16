# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 09:26:05 by rakman            #+#    #+#              #
#    Updated: 2025/01/02 14:45:06 by rakman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	printf/ft_printf.c					\
		printf/ft_handle_char.c				\
		printf/ft_handle_string.c			\
		printf/ft_handle_dec_int.c			\
		printf/ft_handle_unsigned_int.c		\
		printf/ft_handle_hexadecimal.c		\
		printf/ft_handle_address.c			\
		printf/ft_itoa_base.c

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
	
$(NAME):	$(OBJS)
			$(MAKE) -C ./libft
			cp ./libft/libft.a $(NAME)
			ar -rcs $(NAME) $(OBJS)
%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf printf/*.o
	rm -rf libft/*.o

fclean: clean
	rm -rf libft/*.a
	rm -rf *.a

re: fclean all
