/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:44:44 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 19:39:19 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	so_long_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->board->wid * 50, \
								game->board->hei * 50, "so_long");
}

void	game_init(t_game *game, t_board *board)
{
	game->game_status = NORMAL;
	game->player = NULL;
	game->enemy = NULL;
	board->hei = 0;
	board->wid = 0;
	board->map = NULL;
	board->collectible = 0;
	board->count_move = 0;
	board->map_exit = 0;
	game->board = board;
}
