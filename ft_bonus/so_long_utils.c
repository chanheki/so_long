/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:13:08 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 19:51:12 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	exit_game(t_game *game)
{
	write(1, "Exit Button : ", 14);
	write(1, "Quit the program in a clean way.\n", 33);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	lose_game(t_game *game)
{
	game->game_status = GAME_OVER;
	game->player->dir = 0;
	write (1, "\033[0;31m==========\n", 18);
	write (1, "\033[0;31mlose game\n", 18);
	write (1, "\033[0;31m==========\n", 18);
}

int	end_game(t_game *game)
{
	game->game_status = GAME_WIN;
	write (1, "\033[0;36m==========\n", 18);
	write (1, "\033[0;36mWIN! game\n", 18);
	write (1, "\033[0;36m==========\n", 18);
	write(1, "Escape the program in a clean way.\n", 35);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	error_exitor(char *errmsg)
{
	write (1, "Error\n", 6);
	perror (errmsg);
	exit(0);
}
