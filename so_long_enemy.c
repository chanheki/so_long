/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:25:04 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 19:44:36 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	enemy_init(t_game *game, int enemy_count)
{
	int		wid;
	int		hei;
	t_enemy	*enemy;

	enemy = ft_calloc(0, sizeof(t_enemy) * enemy_count);
	enemy->dir = KEYBOARD_D;
	enemy->frame = 0;
	game->enemy = &enemy;
	enemy->enemy_up[0] = mxfti(game->mlx, PLAYER_UP, &wid, &hei);
	enemy->enemy_down[0] = mxfti(game->mlx, PLAYER_DOWN, &wid, &hei);
	enemy->enemy_right[0] = mxfti(game->mlx, PLAYER_RIGHT, &wid, &hei);
	enemy->enemy_left[0] = mxfti(game->mlx, PLAYER_LEFT, &wid, &hei);
	enemy->enemy_up[1] = mxfti(game->mlx, PLAYER_UP_01, &wid, &hei);
	enemy->enemy_down[1] = mxfti(game->mlx, PLAYER_DOWN_01, &wid, &hei);
	enemy->enemy_right[1] = mxfti(game->mlx, PLAYER_RIGHT_01, &wid, &hei);
	enemy->enemy_left[1] = mxfti(game->mlx, PLAYER_LEFT_01, &wid, &hei);
	enemy->enemy_up[2] = mxfti(game->mlx, PLAYER_UP_02, &wid, &hei);
	enemy->enemy_down[2] = mxfti(game->mlx, PLAYER_DOWN_02, &wid, &hei);
	enemy->enemy_right[2] = mxfti(game->mlx, PLAYER_RIGHT_02, &wid, &hei);
	enemy->enemy_left[2] = mxfti(game->mlx, PLAYER_LEFT_02, &wid, &hei);
	player_position(game);
}

static void	draw_enemy_dir(t_game *game, int dir, int key_code)
{
	
}

void	draw_player(t_game *game, int key_code)
{
	if (game->frame < MAX_FRAME / 3)
		draw_player_dir(game, 0, key_code);
	else if (game->frame > (MAX_FRAME / 3) * 2)
		draw_player_dir(game, 2, key_code);
	else
		draw_player_dir(game, 1, key_code);
}
