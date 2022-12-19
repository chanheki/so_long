/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:54:48 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 22:47:51 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	game_init(t_game *game, t_board *board)
{
	board->hei = 0;
	board->wid = 0;
	board->map = NULL;
	board->collectible = 0;
	board->count_move = 0;
	board->map_exit = 0;
	game->board = board;
	game->mlx = NULL;
	game->win = NULL;
	game->tile = NULL;
	game->wall = NULL;
	game->cat_down = NULL;
	game->cat_left = NULL;
	game->cat_right = NULL;
	game->cat_up = NULL;
	game->rat = NULL;
	game->box_open = NULL;
	game->box_close = NULL;
}

int	main(int argc, char *argv[])
{
	t_game	game;
	t_board	board;

	if (argc == 2)
	{
		game_init(&game, &board);
		map_read(argv[1], &game);
		game.mlx = mlx_init();
		game.win = mlx_new_window(game.mlx, game.board->wid * 50, \
								game.board->hei * 50, "so_long");
		img_set(&game);
		map_set(&game, 2, game.board->collectible);
		mlx_key_hook(game.win, key_handler, &game);
		mlx_hook(game.win, ON_DESTROY, 0, exit_game, &game);
		mlx_loop(game.mlx);
	}
	else
		perror ("Usage: ./so_long [MAP_FILE.ber]\n");
	return (0);
}

int	exit_game(t_game *game)
{
	write(1, "user exit\n", 10);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	end_game(t_game *game)
{
	print_step_count(game->board->count_move + 1, 0);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	ret_error(char *errmsg)
{
	write (1, "Error\n", 6);
	perror (errmsg);
	exit(0);
}

void	print_step_count(int count_move, int flag)
{
	if (flag)
		write(1, "step count: ", 12);
	else
		write(1, "\ngame over!! step count: ", 25);
	// ft_putnbr(count_move);
	ft_putnbr_fd(count_move, 0);
	write(1, " steps\n", 7);
}

//arch -x86_64 gcc -L./mlx -lmlx -framework OpenGL -framework AppKit main.c
