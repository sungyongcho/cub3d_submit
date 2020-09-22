# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/02 18:03:49 by sucho             #+#    #+#              #
#    Updated: 2020/09/23 05:54:37 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D
LIBFT					=	libft.a
MINILIBX				=	libmlx.a

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
RM						=	rm -f

INCLUDES_PATH			=	./includes/
LIBFT_PATH				=	./includes/libft/
GET_NEXT_LINE_PATH		=	./includes/get_next_line/
MINILIBX_MMS			=	./includes/minilibx_mms_20200219/
MINILIBX_OPENGL			=	./includes/mlx_openGL/
MINILIBX_LINUX			=	./includes/minilibx_linux/

INCS					=	-I${INCLUDES_PATH} -I${LIBFT_PATH} -I${MINILIBX_MMS}
INCLIB_OPENGL			=	-L${MINILIBX_OPENGL} -lmlx -framework OpenGL -framework Appkit \
							-L${LIBFT_PATH} -lft
INCLIB_MMS				=	-L${MINILIBX_MMS} -lmlx -framework Cocoa -framework Metal \
							-framework MetalKit -framework QuartzCore -L${LIBFT_PATH} -lft

SRCS					=	./includes/get_next_line/get_next_line.c \
							./srcs/main.c \
							./srcs/init.c \
							./srcs/init_vector.c \
							./srcs/cub_parse.c \
							./srcs/cub_parse_path.c \
							./srcs/cub_parse_news.c \
							./srcs/cub_parse_map.c \
							./srcs/cub_set_player.c \
							./srcs/raycast_wall.c \
							./srcs/raycast_rest.c \
							./srcs/key_wasd.c \
							./srcs/key_lr.c \
							./srcs/bmp.c \
							./srcs/map_validity.c \
							./srcs/error_process.c \
							./srcs/screen_exit.c

OBJS					=	${SRCS:.c=.o}

.c.o:
							${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 						$(NAME)

${NAME}:					${OBJS}
							make bonus -C ${LIBFT_PATH}
							make -C ${MINILIBX_OPENGL}
							$(CC) $(CFLAGS) ${INCS} ${INCLIB_OPENGL} -o $(NAME) $(OBJS)

clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							$(MAKE) -C $(MINILIBX_OPENGL) clean
							rm -f $(OBJS) $(MINILIBX)

fclean: 					clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							rm -f $(NAME)

re: 						fclean all

.PHONY: 					all clean fclean re
