/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:07:18 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 23:11:47 by chanheki         ###   ########.fr       */
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

void	img_set(t_game *game)
{
	int	wid;
	int	hei;

	game->wall = mlx_xpm_file_to_image(game->mlx, WALL, &wid, &hei);
	game->tile = mlx_xpm_file_to_image(game->mlx, TILE, &wid, &hei);
	game->cat_up = mlx_xpm_file_to_image(game->mlx, CAT_UP, &wid, &hei);
	game->cat_down = mlx_xpm_file_to_image(game->mlx, CAT_DOWN, &wid, &hei);
	game->cat_right = mlx_xpm_file_to_image(game->mlx, CAT_RIGHT, &wid, &hei);
	game->cat_left = mlx_xpm_file_to_image(game->mlx, CAT_LEFT, &wid, &hei);
	game->rat = mlx_xpm_file_to_image(game->mlx, RAT, &wid, &hei);
	game->box_close = mlx_xpm_file_to_image(game->mlx, BOX_CLOSE, &wid, &hei);
	game->box_open = mlx_xpm_file_to_image(game->mlx, BOX_OPEN, &wid, &hei);
}

void	map_set(t_game *game, int key_code, int collectible)
{
	int	x;
	int	y;

	print_cat_move(game->board->count_move, 1);
	x = game->board->hei;
	while (x--)
	{
		y = game->board->wid;
		while (y--)
		{
			if (game->board->map[x][y] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall,
					y * 50, x * 50);
			else if (game->board->map[x][y] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->tile,
					y * 50, x * 50);
			else if (game->board->map[x][y] == 'P')
				put_cat_image(game, x, y, key_code);
			else if (game->board->map[x][y] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->rat,
					y * 50, x * 50);
			else if (game->board->map[x][y] == 'E')
				put_box_image(game, x, y, collectible);
		}
	}
}

void	put_box_image(t_game *g, int hei, int wid, int collectible)
{
	if (collectible == 0)
		mlx_put_image_to_window(g->mlx, g->win, g->box_open,
			wid * 50, hei * 50);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->box_close,
			wid * 50, hei * 50);
}

void	put_cat_image(t_game *game, int height, int width, int key_code)
{
	if (key_code == 13)
		mlx_put_image_to_window(game->mlx, game->win, game->cat_up,
			width * 50, height * 50);
	else if (key_code == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->cat_left,
			width * 50, height * 50);
	else if (key_code == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->cat_down,
			width * 50, height * 50);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->cat_right,
			width * 50, height * 50);
}
