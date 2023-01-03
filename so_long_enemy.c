/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 03:35:49 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	enemy_init(t_game *game, t_enemy *enemy)
{
	int		wid;
	int		hei;

	game->enemy = enemy;
	enemy->frame = 0;
	enemy->dir = KEYBOARD_D;
	enemy->move = 0;
	enemy->enemy_up[0] = mxfti(game->mlx, ENEMY_UP, &wid, &hei);
	enemy->enemy_down[0] = mxfti(game->mlx, ENEMY_DOWN, &wid, &hei);
	enemy->enemy_right[0] = mxfti(game->mlx, ENEMY_RIGHT, &wid, &hei);
	enemy->enemy_left[0] = mxfti(game->mlx, ENEMY_LEFT, &wid, &hei);
	enemy->enemy_up[1] = mxfti(game->mlx, ENEMY_UP_01, &wid, &hei);
	enemy->enemy_down[1] = mxfti(game->mlx, ENEMY_DOWN_01, &wid, &hei);
	enemy->enemy_right[1] = mxfti(game->mlx, ENEMY_RIGHT_01, &wid, &hei);
	enemy->enemy_left[1] = mxfti(game->mlx, ENEMY_LEFT_01, &wid, &hei);
}

void	draw_enemy_dir(t_game *game, int dir, int key_code)
{
	if (key_code == KEYBOARD_W)
		mpitw(game, game->enemy->enemy_up[dir],
			game->enemy->y * WIDTH, game->enemy->x * HEIGHT);
	else if (key_code == KEYBOARD_A)
		mpitw(game, game->enemy->enemy_left[dir],
			game->enemy->y * WIDTH, game->enemy->x * HEIGHT);
	else if (key_code == KEYBOARD_S)
		mpitw(game, game->enemy->enemy_down[dir],
			game->enemy->y * WIDTH, game->enemy->x * HEIGHT);
	else
		mpitw(game, game->enemy->enemy_right[dir],
			game->enemy->y * WIDTH, game->enemy->x * HEIGHT);
}

void	draw_enemy(t_game *game, int key_code)
{
	if (game->enemy->frame < ENEMY_MAX_FRAME / 2)
		draw_enemy_dir(game, 0, key_code);
	else
		draw_enemy_dir(game, 1, key_code);
}

int	dir_enemy(t_game *game, int x, int y)
{
	int	dir;
	int	dx;
	int	dy;

	game->enemy->x = x;
	game->enemy->y = y;
	dx = game->player->x - x;
	dy = game->player->y - y;
	dir = KEYBOARD_A;
	if (ft_abs(dx) >= ft_abs(dy))
	{	
		if (dy < 0)
			dir = KEYBOARD_S;
		else
			dir = KEYBOARD_W;
	}
	else
	{
		if (dx > 0)
			dir = KEYBOARD_D;
	}
	return (dir);
}

void	draw_enemy_move(t_game *game)
{
	int	x;
	int	y;

	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == '0')
				mpitw(game, game->tile, y * WIDTH, x * HEIGHT);
			else if (game->board->map[x][y] == 'B' ||
						game->board->map[x][y] == 'b')
			{
				game->enemy->x = x;
				game->enemy->y = y;
				draw_enemy(game, dir_enemy(game, x, y));
			}
		}
	}
}

void	move_enemy(t_game *game, int x, int y, int dir)
{
	const int	dx[14] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	const int	dy[14] = {-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	game->enemy->x = x;
	game->enemy->y = y;
	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'P')
		lose_game(game);
	else if (game->board->map[x + dx[dir]][y + dy[dir]] != '1' &&
				game->board->map[x + dx[dir]][y + dy[dir]] != 'E' &&
					game->board->map[x + dx[dir]][y + dy[dir]] != 'C' &&
						game->board->map[x + dx[dir]][y + dy[dir]] != 'B' &&
							game->board->map[x + dx[dir]][y + dy[dir]] != 'b')
	{
		game->board->map[x][y] = '0';
		game->board->map[x + dx[dir]][y + dy[dir]] = 'b';
		game->enemy->x = x + dx[dir];
		game->enemy->y = y + dy[dir];
	}
	game->enemy->dir = dir;
	mpitw(game, game->tile, y * WIDTH, x * HEIGHT);
	draw_enemy(game, dir_enemy(game, game->enemy->x, game->enemy->y));
	// draw_enemy_move(game);
}

void	find_enemy(t_game *game)
{
	int			x;
	int			y;

	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == 'B')
			{
				move_enemy(game, x, y, dir_enemy(game, x, y));
			}
		}
	}
	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == 'b')
				game->board->map[x][y] = 'B';
		}
	}
}
