/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/22 00:16:32 by chanheki         ###   ########.fr       */
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
	enemy->enemy_up[0] = NULL;
	enemy->enemy_down[0] = NULL;
	enemy->enemy_right[0] = NULL;
	enemy->enemy_left[0] = NULL;
	if (game->board->enemy_count)
	{
		enemy->enemy_up[0] = mxfti(game->mlx, ENEMY_UP, &wid, &hei);
		enemy->enemy_down[0] = mxfti(game->mlx, ENEMY_DOWN, &wid, &hei);
		enemy->enemy_right[0] = mxfti(game->mlx, ENEMY_RIGHT, &wid, &hei);
		enemy->enemy_left[0] = mxfti(game->mlx, ENEMY_LEFT, &wid, &hei);
		enemy->enemy_up[1] = mxfti(game->mlx, ENEMY_UP_01, &wid, &hei);
		enemy->enemy_down[1] = mxfti(game->mlx, ENEMY_DOWN_01, &wid, &hei);
		enemy->enemy_right[1] = mxfti(game->mlx, ENEMY_RIGHT_01, &wid, &hei);
		enemy->enemy_left[1] = mxfti(game->mlx, ENEMY_LEFT_01, &wid, &hei);
	}
}

void	draw_enemy_dir(t_game *game, int dir, int key_code)
{
	if (key_code == KEYBOARD_W)
		mpitw(game, game->enemy->enemy_up[dir],
			game->enemy->y * 50, game->enemy->x * 50);
	else if (key_code == KEYBOARD_A)
		mpitw(game, game->enemy->enemy_left[dir],
			game->enemy->y * 50, game->enemy->x * 50);
	else if (key_code == KEYBOARD_S)
		mpitw(game, game->enemy->enemy_down[dir],
			game->enemy->y * 50, game->enemy->x * 50);
	else
		mpitw(game, game->enemy->enemy_right[dir],
			game->enemy->y * 50, game->enemy->x * 50);
}

void	draw_enemy(t_game *game, int key_code)
{
	if (game->enemy->frame < ENEMY_MAX_FRAME / 3)
		draw_enemy_dir(game, 0, key_code);
	else if (game->enemy->frame > (ENEMY_MAX_FRAME / 3) * 2)
		draw_enemy_dir(game, 2, key_code);
	else
		draw_enemy_dir(game, 1, key_code);
}

void	move_enemy(t_game *game, int x, int y, int dir)
{
	const int	dx[14] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	const int	dy[14] = {-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	game->enemy->x = x;
	game->enemy->y = y;
	if (game->board->map[x + dx[dir]][y + dy[dir]] != '1' &&
				game->board->map[x + dx[dir]][y + dy[dir]] != 'E')
	{
		game->board->map[x][y] = '0';
		game->board->map[x + dx[dir]][y + dy[dir]] = 'e';
		game->enemy->x = x + dx[dir];
		game->enemy->y = y + dy[dir];
	}
	game->enemy->dir = dir;
	draw_enemy(game, dir);
}

int	dir_enemy(t_game *game, int x, int y)
{
	int	dir;
	int	dx;
	int	dy;

	dx = game->player->x - x;
	dy = game->player->y - y;
	dir = KEYBOARD_W;
	if (ft_abs(dx) > ft_abs(dy))
	{
		if (dx < 0)
			dir = KEYBOARD_A;
		else
			dir = KEYBOARD_D;
	}
	if (dy < 0)
		dir = KEYBOARD_S;
	return (dir);
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
			if (game->board->map[x][y] == 'e')
				break ;
		}
		if (game->board->map[x][y] == 'e')
			move_enemy(game, x, y, dir_enemy(game, x, y));
	}
}
