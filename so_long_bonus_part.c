/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:28:37 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 23:17:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	draw_step_count(t_game *game)
{
	char	*str;

	mpitw(game, game->wall, 0 * WIDTH, 0 * HEIGHT);
	str = ft_itoa(game->board->count_move);
	mlx_string_put(game->mlx, game->win, 4, 10, 0xFFFFFF, str);
	free(str);
}

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
