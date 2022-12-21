/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:55:01 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 20:51:15 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// # include <mlx.h>
# include "mlx/mlx.h"
# include "lib/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define PLAYER_MAX_FRAME	30
# define ENEMY_MAX_FRAME	30
# define WIDTH				50
# define HEIGHT				50

# define ASSET_PATH	"./asset"

# define TILE "./asset/tile.xpm"
# define WALL "./asset/wall.xpm"
# define COLLECT "./asset/collect.xpm"
# define EXIT_OPEN "./asset/exit_open.xpm"
# define EXIT_CLOSE "./asset/exit_close.xpm"

# define PLAYER_UP "./asset/player_w00.xpm"
# define PLAYER_DOWN "./asset/player_s00.xpm"
# define PLAYER_RIGHT "./asset/player_d00.xpm"
# define PLAYER_LEFT "./asset/player_a00.xpm"

# define PLAYER_UP_01 "./asset/player_w01.xpm"
# define PLAYER_DOWN_01 "./asset/player_s01.xpm"
# define PLAYER_RIGHT_01 "./asset/player_d01.xpm"
# define PLAYER_LEFT_01 "./asset/player_a01.xpm"

# define PLAYER_UP_02 "./asset/player_w02.xpm"
# define PLAYER_DOWN_02 "./asset/player_s02.xpm"
# define PLAYER_RIGHT_02 "./asset/player_d02.xpm"
# define PLAYER_LEFT_02 "./asset/player_a02.xpm"

# define ENEMY_UP "./asset/enemy_w00.xpm"
# define ENEMY_DOWN "./asset/enemy_s00.xpm"
# define ENEMY_RIGHT "./asset/enemy_d00.xpm"
# define ENEMY_LEFT "./asset/enemy_a00.xpm"

# define ENEMY_UP_01 "./asset/enemy_w01.xpm"
# define ENEMY_DOWN_01 "./asset/enemy_s01.xpm"
# define ENEMY_RIGHT_01 "./asset/enemy_d01.xpm"
# define ENEMY_LEFT_01 "./asset/enemy_a01.xpm"

# define ENEMY_UP_02 "./asset/enemy_w02.xpm"
# define ENEMY_DOWN_02 "./asset/enemy_s02.xpm"
# define ENEMY_RIGHT_02 "./asset/enemy_d02.xpm"
# define ENEMY_LEFT_02 "./asset/enemy_a02.xpm"

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
	int		enemy_count;
}	t_board;

/* player */
typedef struct s_player
{
	int		frame;
	int		dir;
	int		x;
	int		y;
	void	*player_up[3];
	void	*player_down[3];
	void	*player_right[3];
	void	*player_left[3];
}	t_player;

typedef struct s_enemy
{
	int		frame;
	int		type;
	int		dir;
	int		x;
	int		y;
	void	*enemy_up[3];
	void	*enemy_down[3];
	void	*enemy_right[3];
	void	*enemy_left[3];
}	t_enemy;

/* so_long game */
typedef struct s_game
{
	t_board		*board;
	t_player	*player;
	t_enemy		**enemy;
	void		*mlx;
	void		*win;
	void		*tile;
	void		*wall;
	void		*collect;
	void		*exit_close;
	void		*exit_open;
}	t_game;

/* so_long func */
void	checkerset(t_game *checker, t_game *game);
int		end_game(t_game *game);
int		exit_game(t_game *game);
void	ret_error(char *errmsg);
void	print_step_count(int count_move, int flag);

void	check_validate_board(t_game *game, char *str);

void	img_init(t_game *game);
void	map_set(t_game *game, int key_code, int collectible);
void	map_read(char *filename, t_game *game);
void	put_box_image(t_game *g, int hei, int wid, int collectible);
void	draw_player(t_game *game, int key_code);

void	player_position(t_game *game);
int		key_handler(int key, t_game *game);

void	so_long_init(t_game *game);
void	game_init(t_game *game, t_board *board);
void	player_init(t_game *game, t_player *player);
void	enemy_init(t_game *game, int enemy_count);

void	*mxfti(void *xvar, char *file, int *width, int *height);
int		mpitw(t_game *game, void *img_ptr, int x, int y);
#endif
