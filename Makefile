# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 18:05:34 by chanheki          #+#    #+#              #
#    Updated: 2023/01/17 20:40:53 by chanheki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- NAME ---- #

NAME		= so_long

LIBFT		= ./lib/libft.a
LIBFTCC		= -L./lib -lft

MLX			=	./mlx/libmlx.a
MLXCC		=	-L./mlx -lmlx
MLX_FLAGS	=	-framework OpenGL -framework Appkit

CC = cc
CFLAGS = -Wall -Wextra -Werror $(DBGS)
DBGS = -fsanitize=address -g3

AR = ar
ARFLAG = ruc
RM = rm -rf

object_dir = ./objects

# ---- escape ---- #

DELINE = \033[K
CURSUP = \033[A

RESET = \033[0m
RESTINT = \033[22m

BOLD = \033[1m

MAGENTA = \033[35m
GREEN = \033[32m
RED = \033[31m

# ---- Mandatory ---- #

sources1 :=	

sources1 += ft_mandatory/so_long_main.c
sources1 += ft_mandatory/get_next_line.c 
sources1 += ft_mandatory/so_long_enemy_move.c 
sources1 += ft_mandatory/so_long_enemy.c 
sources1 += ft_mandatory/so_long_frame.c 
sources1 += ft_mandatory/so_long_init.c 
sources1 += ft_mandatory/so_long_key_handler.c 
sources1 += ft_mandatory/so_long_lose.c 
sources1 += ft_mandatory/so_long_map_check.c 
sources1 += ft_mandatory/so_long_map_utils.c 
sources1 += ft_mandatory/so_long_mlx.c 
sources1 += ft_mandatory/so_long_player.c 
sources1 += ft_mandatory/so_long_utils.c

# ---- Bonus ---- #

sources2 :=	

sources2 += ft_bonus/so_long_bonus_main.c
sources2 += ft_bonus/get_next_line.c 
sources2 += ft_bonus/so_long_key_handler.c 
sources2 += ft_bonus/so_long_map_check.c 
sources2 += ft_bonus/so_long_map_utils.c 
sources2 += ft_bonus/so_long_bonus_part.c 
sources2 += ft_bonus/so_long_enemy.c 
sources2 += ft_bonus/so_long_frame.c 
sources2 += ft_bonus/so_long_init.c 
sources2 += ft_bonus/so_long_mlx.c 
sources2 += ft_bonus/so_long_player.c 
sources2 += ft_bonus/so_long_utils.c

# ---- Elements ---- #

all_sources = $(sources1) $(sources2)

objects1 = $(sources1:.c=.o)
objects2 = $(sources2:.c=.o)
all_objects = $(objects1) $(objects2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), objects2, objects1))) 
endef

define react
$(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)
endef

# ---- Command ---- #

.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : $(objects_goal) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $(objects_goal) $(LIBFTCC) $(MLXCC) $(MLX_FLAGS)
	@echo "$(DELINE) $(MAGENTA)$@ $(RESET) is compiled $(GREEN)$(BOLD) OK ✅ $(RESET)"

bonus : $(NAME)

$(object_dir)/%.o : %.c
	@#mkdir -p $(object_dir)
	@mkdir -p $(object_dir)/$(dir $^)
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo " $(MAGENTA)$(NAME) $(RESET)objects file compiling... $(DELINE)$(GREEN) $^ $(RESET)$(CURSUP)"

$(LIBFT) :
	@make -C ./lib all

$(MLX) :
	@make -C ./mlx all

clean :
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)
	@make -C ./lib clean
	@make -C ./mlx clean
	@echo "$(RED) Delete$(BOLD) objects $(RESTINT)file $(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@make -C ./lib fclean
	@make -C ./mlx clean
	@echo "$(RED) Delete$(BOLD) $(NAME) $(RESTINT)file $(RESET)"

re : fclean
	@make $(react)