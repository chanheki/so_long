/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:07:18 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/22 00:16:03 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	map_read(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		ret_error("fd error");
	line = get_next_line(fd);
	game->board->wid = ft_strlen(line) - 1;
	str = ft_strdup("");
	while (line)
	{
		game->board->hei++;
		str = ft_strjoin(str, line);
		free(line);
		line = get_next_line(fd);
	}
	check_validate_board(game, str);
	game->board->map = ft_split(str, '\n');
	free(str);
	close(fd);
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

static void	draw_step_count(t_game *game)
{
	char	*str;

	str = ft_itoa(game->board->count_move);
	mlx_string_put(game->mlx, game->win, 4, 10, 0xFFFFFF, str);
	free(str);
}

void	map_set(t_game *game, int key_code, int collectible)
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
				mpitw(game, game->wall,
					y * 50, x * 50);
			else if (game->board->map[x][y] == '0')
				mpitw(game, game->tile,
					y * 50, x * 50);
			else if (game->board->map[x][y] == 'P')
				draw_player(game, key_code);
			else if (game->board->map[x][y] == 'C')
				mpitw(game, game->collect,
					y * 50, x * 50);
			else if (game->board->map[x][y] == 'E')
				put_box_image(game, x, y, collectible);
			else if (game->board->map[x][y] == 'e')
				move_enemy(game, x, y, dir_enemy(game, x, y));
		}
	}
	draw_step_count(game);
}

void	put_box_image(t_game *g, int hei, int wid, int collectible)
{
	if (collectible == 0)
		mlx_put_image_to_window(g->mlx, g->win, g->exit_open,
			wid * 50, hei * 50);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->exit_close,
			wid * 50, hei * 50);
}
