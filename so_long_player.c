/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 22:47:54 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	player_position(t_game *game)
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
	game->player->x = x;
	game->player->y = y;
}

void	player_init(t_game *game, t_player *player)
{
	int	wid;
	int	hei;

	player->dir = KEYBOARD_D;
	player->frame = 0;
	game->player = player;
	player->player_up[0] = mxfti(game->mlx, PLAYER_UP, &wid, &hei);
	player->player_down[0] = mxfti(game->mlx, PLAYER_DOWN, &wid, &hei);
	player->player_right[0] = mxfti(game->mlx, PLAYER_RIGHT, &wid, &hei);
	player->player_left[0] = mxfti(game->mlx, PLAYER_LEFT, &wid, &hei);
	player->player_up[1] = mxfti(game->mlx, PLAYER_UP_01, &wid, &hei);
	player->player_down[1] = mxfti(game->mlx, PLAYER_DOWN_01, &wid, &hei);
	player->player_right[1] = mxfti(game->mlx, PLAYER_RIGHT_01, &wid, &hei);
	player->player_left[1] = mxfti(game->mlx, PLAYER_LEFT_01, &wid, &hei);
	player->player_up[2] = mxfti(game->mlx, PLAYER_UP_02, &wid, &hei);
	player->player_down[2] = mxfti(game->mlx, PLAYER_DOWN_02, &wid, &hei);
	player->player_right[2] = mxfti(game->mlx, PLAYER_RIGHT_02, &wid, &hei);
	player->player_left[2] = mxfti(game->mlx, PLAYER_LEFT_02, &wid, &hei);
	player_position(game);
}

static void	draw_player_dir(t_game *game, int dir, int key_code)
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

void	draw_player(t_game *game, int key_code)
{
	if (game->player->frame < PLAYER_MAX_FRAME / 3)
		draw_player_dir(game, 0, key_code);
	else if (game->player->frame > (PLAYER_MAX_FRAME / 3) * 2)
		draw_player_dir(game, 2, key_code);
	else
		draw_player_dir(game, 1, key_code);
}
