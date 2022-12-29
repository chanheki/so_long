/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:07:18 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/29 22:29:16 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static char	*so_long_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	total_length;

	if (!s1 || !s2)
		return (NULL);
	total_length = (ft_strlen(s1) + ft_strlen(s2) + 1);
	result = (char *)malloc(sizeof(char) * total_length);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_length);
	ft_strlcat(result, s2, total_length);
	free(s1);
	free(s2);
	return (result);
}

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
		str = so_long_strjoin(str, line);
		line = get_next_line(fd);
	}
	check_validate_board(game, str);
	game->board->map = ft_split(str, '\n');
	free(str);
	free(line);
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
			else if (game->board->map[x][y] == 'e')
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
			else if (game->board->map[x][y] == 'e')
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
		mpitw(game, game->exit_open,
				game->exit_y * WIDTH, game->exit_x * HEIGHT);
	}
}
