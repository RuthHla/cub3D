# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 20:45:59 by sleroy            #+#    #+#              #
#    Updated: 2024/11/26 10:56:07 by sleroy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCFILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			ft_lstadd_back.c ft_lstnew.c

OBJFILES = $(SRCFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -f

$(NAME): $(OBJFILES)
			ar rc $(NAME) $(OBJFILES)
			ranlib $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
			$(RM) $(OBJFILES)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
