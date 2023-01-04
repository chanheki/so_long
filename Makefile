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

DBGS		=	-fsanitize=address -g3

MLX_NAME	=	mlx
MLX_DIR		=	./mlx
MLX_REPO	=	-L./mlx -lmlx 
MLX_FLAGS	=	-framework OpenGL -framework Appkit

SRCS		=	so_long.c \
				key_handler.c \
				map_check.c \
				map_utils.c \
				get_next_line.c \
				so_long_init.c \
				so_long_mlx.c \
				so_long_player.c \
				so_long_enemy.c \
				so_long_enemy_util.c \
				so_long_frame.c \
				so_long_bonus_part.c \
				so_long_utils.c

SRCS_BONUS	=	so_long_utils_bonus.c \
				so_long_bonus.c \
				so_long.c \
				key_handler.c \
				map_check.c \
				map_utils.c \
				get_next_line.c \
				so_long_init.c \
				so_long_mlx.c \
				so_long_player.c \
				so_long_enemy.c \
				so_long_enemy_util.c \
				so_long_frame.c \
				so_long_bonus_part.c

OBJS		=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m

all : $(NAME)

bonus : $(NAME)
    @make OBJS='$(OBJS_BONUS)'

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	make -C $(MLX_DIR)
	cp $(LIB_DIR)/$(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -l$(MLX_NAME) $(MLX_REPO) $(MLX_FLAGS) $(LIB_DIR)/$(LIBFT)
	make fclean -C $(LIB_DIR)
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"
	@echo "$(YELLOW)|         so_long   compile finished.         |$(DEF_COLOR)"
	@echo "$(YELLOW)===============================================$(DEF_COLOR)"

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY = all clean fclean re bonus
