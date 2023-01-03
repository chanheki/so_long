/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:44:44 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 03:12:11 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	so_long_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->board->wid * WIDTH, \
								game->board->hei * HEIGHT, "so_long");
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

void	img_init(t_game *game)
{
	int	wid;
	int	hei;

	game->wall = mxfti(game->mlx, WALL, &wid, &hei);
	game->tile = mxfti(game->mlx, TILE, &wid, &hei);
	game->collect = mxfti(game->mlx, COLLECT, &wid, &hei);
	game->exit_close = mxfti(game->mlx, EXIT_CLOSE, &wid, &hei);
	game->exit_open = mxfti(game->mlx, EXIT_OPEN, &wid, &hei);
}

void	exit_init(t_game *game, int x, int y)
{
	game->exit_x = x;
	game->exit_y = y;
	game->board->map[x][y] = '0';
}

void	check_exit(t_game *game)
{
	if (game->board->collectible == 0)
	{
		game->board->map[game->exit_x][game->exit_y] = 'E';
		mpitw(game, game->exit_open, \
				game->exit_y * WIDTH, game->exit_x * HEIGHT);
	}
}
