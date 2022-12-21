# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanheki <chanheki@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 16:31:36 by chanheki            #+#    #+#              #
#    Updated: 2022/12/12 22:14:19 by chanheki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

LIB_DIR		=	./lib
LIBFT		=	libft.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

AR			=	ar
ARFLAGS		=	rcsu

DBGS		=	-fsanitize=address -d3

MLX_NAME	=	mlx
MLX_DIR		=	./mlx
MLX_REPO	=	-L./mlx -lmlx 
MLX_FLAGS	=	-framework OpenGL -framework Appkit

SRCS		=	so_long.c \
				so_long_utils.c \
				key_handler.c \
				map_check.c \
				map_utils.c \
				get_next_line.c \
				so_long_init.c \
				so_long_mlx.c \
				so_long_player.c

OBJS	=	$(SRCS:.c=.o)

# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m

all : $(NAME)

bonus : $(NAME)

debug : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	cp $(LIB_DIR)/$(LIBFT) $(NAME)
	$(CC) $(CFLAGS) -l$(MLX_NAME) $(MLX_REPO) $(MLX_FLAGS) $(OBJS) $(LIB_DIR)/$(LIBFT) -o $(NAME) $(if $(filter debug, $(MAKECMDGOALS)), $(DBGS))
	make fclean -C $(LIB_DIR)
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"
	@echo "$(YELLOW)|         so_long   compile finished.         |$(DEF_COLOR)"
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"

clean:
	rm -rf $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY = all clean fclean re
