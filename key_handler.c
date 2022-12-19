/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:23:46 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 23:48:17 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	player_position(t_game *game, int *cur_x, int *cur_y)
{
	int			x;
	int			y;

	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == 'P')
				break ;
		}
		if (game->board->map[x][y] == 'P')
			break ;
	}
	*cur_x = x;
	*cur_y = y;
}

static void	press_key(t_game *game, int dir)
{
	const int	dx[14] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	const int	dy[14] = {-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int			x;
	int			y;

	player_position(game, &x, &y);
	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'C')
		game->board->collectible -= 1;
	if (game->board->map[x + dx[dir]][y + dy[dir]] == 'E' &&
			game->board->collectible == 0)
		end_game(game);
	else if (game->board->map[x + dx[dir]][y + dy[dir]] != '1' &&
				game->board->map[x + dx[dir]][y + dy[dir]] != 'E')
	{
		game->board->map[x][y] = '0';
		game->board->map[x + dx[dir]][y + dy[dir]] = 'P';
		game->board->count_move += 1;
	}
	map_set(game, dir, game->board->collectible);
}

int	key_handler(int key, t_game *game)
{
	if (key == KEYBOARD_A || key == KEYBOARD_S
		|| key == KEYBOARD_D || key == KEYBOARD_W)
		press_key(game, key);
	if (key == KEYBOARD_ESC)
		exit(0);
	return (0);
}
