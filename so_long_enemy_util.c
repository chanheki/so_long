/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 22:05:34 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

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
