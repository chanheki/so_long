/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:44:44 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 19:02:26 by chanheki         ###   ########.fr       */
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

void	map_init(t_game *game)
{
	int	x;
	int	y;

	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == '1')
				mpitw(game, game->wall, y * WIDTH, x * HEIGHT);
			else if (game->board->map[x][y] == '0')
				mpitw(game, game->tile, y * WIDTH, x * HEIGHT);
			else if (game->board->map[x][y] == 'P')
				draw_player(game, game->player->dir);
			else if (game->board->map[x][y] == 'E')
				exit_init(game, x, y);
			else if (game->board->map[x][y] == 'C')
				mpitw(game, game->collect, y * WIDTH, x * HEIGHT);
			else if (game->board->map[x][y] == 'B')
				draw_enemy(game, dir_enemy(game, x, y));
		}
	}
}
