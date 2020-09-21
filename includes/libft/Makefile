# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/08 22:03:29 by sucho             #+#    #+#              #
#    Updated: 2020/09/15 19:51:45 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

LIBC		=	ar rc

SRCS		=	./ft_memset.c \
				./ft_bzero.c \
				./ft_memcpy.c \
				./ft_memccpy.c \
				./ft_memmove.c \
				./ft_memchr.c \
				./ft_memcmp.c \
				./ft_strlen.c \
				./ft_strlcpy.c \
				./ft_strlcat.c \
				./ft_strchr.c \
				./ft_strrchr.c \
				./ft_strnstr.c \
				./ft_strncmp.c \
				./ft_strncmp.c \
				./ft_atoi.c \
				./ft_isalpha.c \
				./ft_isdigit.c \
				./ft_isalnum.c \
				./ft_isascii.c \
				./ft_isprint.c \
				./ft_toupper.c \
				./ft_tolower.c \
				./ft_calloc.c \
				./ft_strdup.c \
				./ft_substr.c \
				./ft_strjoin.c \
				./ft_strtrim.c \
				./ft_putchar_fd.c \
				./ft_putstr_fd.c \
				./ft_putendl_fd.c \
				./ft_putnbr_fd.c \
				./ft_itoa.c \
				./ft_strmapi.c \
				./ft_split.c

SRCS_BONUS	=	./ft_lstnew.c \
				./ft_lstadd_front.c \
				./ft_lstsize.c \
				./ft_lstlast.c \
				./ft_lstadd_back.c \
				./ft_lstdelone.c \
				./ft_lstclear.c \
				./ft_lstiter.c \
				./ft_lstmap.c

OBJS		=	${SRCS:.c=.o}
OBJS_BONUS	=	${SRCS_BONUS:.c=.o}
INCS		=	.

.c.o:
				${CC} ${CFLAGS} -c $< -o $(<:.c=.o) -I${INCS}

${NAME}:		${OBJS}
				${LIBC} ${NAME} ${OBJS}

all:			${NAME}

bonus:			${NAME} ${OBJS_BONUS}
				${LIBC} ${NAME} ${OBJS_BONUS}

clean:
				${RM} ${OBJS} ${OBJS_BONUS}

fclean:			clean
				${RM} ${NAME} ${bonus}

re:				fclean all
