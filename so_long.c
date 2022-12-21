/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:54:48 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 20:53:28 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static void	frame_count(t_game *game)
{
	// int	i;

	game->player->frame++;
	if (game->player->frame >= PLAYER_MAX_FRAME)
		game->player->frame = 0;
	// i = 0;
	// while (game->enemy[i])
	// {
	// 	game->enemy[i]->frame++;
	// 	if (game->enemy[i]->frame >= ENEMY_MAX_FRAME)
	// 	game->enemy[i]->frame = 0;
	// 	i++;
	// }
}

static int	main_loop(t_game *game)
{
	frame_count(game);
	draw_player(game, game->player->dir);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game		game;
	t_board		board;
	t_player	player;

	if (argc == 2)
	{
		game_init(&game, &board);
		map_read(argv[1], &game);
		so_long_init(&game);
		player_init(&game, &player);
		// enemy_init(&game, board.enemy_count);
		img_init(&game);
		map_set(&game, 2, game.board->collectible);
		mlx_hook(game.win, ON_KEYDOWN, 0, key_handler, &game);
		mlx_hook(game.win, ON_DESTROY, 0, exit_game, &game);
		mlx_loop_hook(game.mlx, &main_loop, &game);
		mlx_loop(game.mlx);
	}
	else
		perror ("Usage: ./so_long [MAP_FILE.ber]\n");
	return (0);
}
