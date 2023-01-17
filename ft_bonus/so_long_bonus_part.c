/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:28:37 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 20:20:37 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	draw_player_lose(t_game *game)
{
	mpitw(game, game->player->player_lose[game->player->dir], \
				game->player->y * WIDTH, game->player->x * HEIGHT);
}

void	lose_game_shutdown(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	draw_step_count(t_game *game)
{
	char	*str;

	mpitw(game, game->wall, 0 * WIDTH, 0 * HEIGHT);
	str = ft_itoa(game->board->count_move);
	mlx_string_put(game->mlx, game->win, 4, 10, 0xFFFFFF, str);
	free(str);
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
