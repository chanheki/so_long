/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:54:48 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 22:06:34 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static int	main_loop(t_game *game)
{
	frame_count(game);
	if (game->game_status == NORMAL)
	{
		draw_player(game, game->player->dir);
		draw_enemy_move(game);
		if (game->enemy->move == ENEMY_MOVE_FREQ)
			find_enemy(game);
	}
	else if (game->game_status == GAME_OVER)
		draw_player_lose(game);
	else if (game->game_status == SHUTDOWN)
		lose_game_shutdown(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game		game;
	t_board		board;
	t_player	player;
	t_enemy		enemy;

	if (argc == 2)
	{
		game_init(&game, &board);
		map_read(argv[1], &game);
		so_long_init(&game);
		player_init(&game, &player);
		enemy_init(&game, &enemy);
		img_init(&game);
		map_init(&game);
		mlx_hook(game.win, ON_KEYDOWN, 0, key_handler, &game);
		mlx_hook(game.win, ON_DESTROY, 0, exit_game, &game);
		mlx_loop_hook(game.mlx, &main_loop, &game);
		mlx_loop(game.mlx);
	}
	else
		perror ("Usage: ./so_long [MAP_FILE.ber]\n");
	return (0);
}
