/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_lose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:28:37 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 19:24:49 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	draw_player_lose(t_game *game)
{
	mpitw(game, game->player->player_lose[game->player->dir], \
				game->player->y * WIDTH, game->player->x * HEIGHT);
}

void	lose_game_shutdown(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
