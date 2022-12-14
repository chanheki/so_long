/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:54:48 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/04 23:17:07 by chanheki         ###   ########.fr       */
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

void	map_set(t_game *game, int key_code)
{
	int	x;
	int	y;

	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == '0')
				mpitw(game, game->tile, y * WIDTH, x * HEIGHT);
			else if (game->board->map[x][y] == 'P')
				draw_player(game, key_code);
			else if (game->board->map[x][y] == 'B' ||
						game->board->map[x][y] == 'b')
			{
				game->enemy->x = x;
				game->enemy->y = y;
				draw_enemy(game, dir_enemy(game, x, y));
			}
		}
	}
	check_exit(game);
	draw_step_count(game);
}
