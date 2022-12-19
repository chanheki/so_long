/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:55:01 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 23:51:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "lib/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define TILE "./asset/tile.xpm"
# define WALL "./asset/wall.xpm"
# define RAT "./asset/rat.xpm"
# define BOX_OPEN "./asset/box_open.xpm"
# define BOX_CLOSE "./asset/box_close.xpm"
# define CAT_UP "./asset/cat_up.xpm"
# define CAT_DOWN "./asset/cat_down.xpm"
# define CAT_RIGHT "./asset/cat_right.xpm"
# define CAT_LEFT "./asset/cat_left.xpm"

/* mlx_event */
typedef enum e_mlx_event {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_mlx_event;

/* mlx_keycode */

typedef enum e_mlx_keycode {
	KEYBOARD_W = 13,
	KEYBOARD_A = 0,
	KEYBOARD_S = 1,
	KEYBOARD_D = 2,
	KEYBOARD_ESC = 53
}	t_mlx_keycode;

/* get_next_line */
# define BUFFER_SIZE 42

typedef enum e_line
{
	NO_NEW_LINE	= -1
}	t_line;

/* get_next_line func*/
char	*get_next_line(int fd);

/* so_long board */
typedef struct s_board
{
	int		hei;
	int		wid;
	char	**map;

	int		collectible;
	int		count_move;
	int		map_exit;
}	t_board;

/* so_long game */
typedef struct s_game
{
	t_board	*board;

	void	*mlx;
	void	*win;
	void	*tile;
	void	*wall;
	void	*cat_up;
	void	*cat_down;
	void	*cat_right;
	void	*cat_left;
	void	*rat;
	void	*box_close;
	void	*box_open;
}	t_game;

/* so_long func */
void	checkerset(t_game *checker, t_game *game);
int		end_game(t_game *game);
int		exit_game(t_game *game);
void	ret_error(char *errmsg);
void	print_cat_move(int count_move, int flag);

void	check_validate_board(t_game *game, char *str);
void	ft_putnbr(int n);

void	img_set(t_game *game);
void	map_set(t_game *game, int pressed_key, int collectible);
void	map_read(char *filename, t_game *game);
void	put_box_image(t_game *g, int hei, int wid, int collectible);
void	put_cat_image(t_game *game, int height, int width, int key_code);

int		key_handler(int key, t_game *game);
#endif
