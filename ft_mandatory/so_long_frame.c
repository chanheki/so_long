/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:00:02 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 22:47:29 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	frame_normal(t_game *game)
{
	if (game->player->frame >= PLAYER_MAX_FRAME)
		game->player->frame = 0;
	if (game->board->enemy_count)
	{
		game->enemy->frame++;
		if (game->enemy->frame >= ENEMY_MAX_FRAME)
		{
			game->enemy->frame = 0;
			game->enemy->move ++;
			if (game->enemy->move > ENEMY_MOVE_FREQ)
				game->enemy->move = 0;
		}
	}
}

void	frame_game_over(t_game *game)
{
	if (game->player->frame >= PLAYER_LOSE_FRAME)
	{
		game->player->dir ++;
		game->player->frame = 0;
	}
	if (game->player->dir == LOSE_MAX_FRAME)
	{
		game->player->dir = 0;
		game->game_status = SHUTDOWN;
	}
}

void	frame_count(t_game *game)
{
	game->player->frame++;
	if (game->game_status == NORMAL)
		frame_normal(game);
	else if (game->game_status == GAME_OVER)
		frame_game_over(game);
}
