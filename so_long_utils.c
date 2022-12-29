/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:13:08 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 15:44:09 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	exit_game(t_game *game)
{
	write(1, "user exit\n", 10);
	write(1, "\nGame Win!! ", 12);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	lose_game(t_game *game)
{
	game->game_status = GAME_OVER;
	draw_player_lose(game);
	print_step_count(game->board->count_move + 1, 0);
	write (1, "lose game\n", 10);
	if (game->game_status == SHUTDOWN)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
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
		write(1, "step count: ", 13);
	ft_putnbr_fd(count_move, 0);
	write(1, " steps\n", 7);
}
