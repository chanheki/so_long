/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 23:15:15 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	enemy_init(t_game *game)
{
	int		wid;
	int		hei;
	t_enemy	enemy;

	game->enemy = &enemy;
	enemy.frame = 0;
	enemy.dir = KEYBOARD_D;
	game->enemy = &enemy;
	enemy.enemy_up[0] = NULL;
	enemy.enemy_down[0] = NULL;
	enemy.enemy_right[0] = NULL;
	enemy.enemy_left[0] = NULL;
	if (game->board->enemy_count)
	{
		enemy.enemy_up[0] = mxfti(game->mlx, ENEMY_UP, &wid, &hei);
		enemy.enemy_down[0] = mxfti(game->mlx, ENEMY_DOWN, &wid, &hei);
		enemy.enemy_right[0] = mxfti(game->mlx, ENEMY_RIGHT, &wid, &hei);
		enemy.enemy_left[0] = mxfti(game->mlx, ENEMY_LEFT, &wid, &hei);
		enemy.enemy_up[1] = mxfti(game->mlx, ENEMY_UP_01, &wid, &hei);
		enemy.enemy_down[1] = mxfti(game->mlx, ENEMY_DOWN_01, &wid, &hei);
		enemy.enemy_right[1] = mxfti(game->mlx, ENEMY_RIGHT_01, &wid, &hei);
		enemy.enemy_left[1] = mxfti(game->mlx, ENEMY_LEFT_01, &wid, &hei);
	}
}

static void	draw_enemy_dir(t_game *game, int dir, int key_code)
{
	if (key_code == KEYBOARD_W)
		mpitw(game, game->player->player_up[dir],
			game->player->y * 50, game->player->x * 50);
	else if (key_code == KEYBOARD_A)
		mpitw(game, game->player->player_left[dir],
			game->player->y * 50, game->player->x * 50);
	else if (key_code == KEYBOARD_S)
		mpitw(game, game->player->player_down[dir],
			game->player->y * 50, game->player->x * 50);
	else
		mpitw(game, game->player->player_right[dir],
			game->player->y * 50, game->player->x * 50);
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

static void	move_enemy(t_game *game, int x, int y, int dir)
{
	const int	dx[14] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	const int	dy[14] = {-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	if (game->board->map[x + dx[dir]][y + dy[dir]] != '1' &&
				game->board->map[x + dx[dir]][y + dy[dir]] != 'E')
	{
		game->board->map[x][y] = '0';
		game->board->map[x + dx[dir]][y + dy[dir]] = 'e';
	}
	game->enemy->dir = dir;
	map_set(game, dir, game->board->collectible);
}

int	moveplan_enemy(t_game *game, int x, int y)
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
			move_enemy(game, x, y, moveplan_enemy(game, x, y));
	}
}
