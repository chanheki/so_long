/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:23:46 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 04:00:30 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static void	press_key(t_game *game, int dir)
{
	const int	dx[14] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	const int	dy[14] = {-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	const int	x = game->player->x;
	const int	y = game->player->y;

	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'C')
		game->board->collectible -= 1;
	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'B' ||
			game->board->map[x + dx[dir]][y + dy[dir]] == 'b')
		lose_game(game);
	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'E' &&
			game->board->collectible == 0)
		end_game(game);
	else if (game->board->map[x + dx[dir]][y + dy[dir]] != '1' &&
				game->board->map[x + dx[dir]][y + dy[dir]] != 'E')
	{
		game->board->map[x][y] = '0';
		game->player->x += dx[dir];
		game->player->y += dy[dir];
		game->board->map[x + dx[dir]][y + dy[dir]] = 'P';
		game->board->count_move += 1;
		print_step_count(game);
	}
	game->player->dir = dir;
	map_set(game, dir);
}

int	key_handler(int key, t_game *game)
{
	if (game->game_status == NORMAL)
	{
		if (key == KEYBOARD_A || key == KEYBOARD_S
			|| key == KEYBOARD_D || key == KEYBOARD_W)
			press_key(game, key);
	}
	if (key == KEYBOARD_ESC)
	{
		write(1, "ESC key : ", 10);
		exit_game(game);
	}
	return (0);
}
