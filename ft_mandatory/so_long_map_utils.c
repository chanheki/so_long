/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:07:18 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 19:02:10 by chanheki         ###   ########.fr       */
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

static void	map_read_end(char *str, char *line, int fd)
{
	free(str);
	free(line);
	close(fd);
}

void	map_read(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		error_exitor("fd error");
	line = get_next_line(fd);
	if (line == NULL)
		error_exitor("no data");
	game->board->wid = ft_strlen(line) - 1;
	str = ft_strdup("");
	while (line)
	{
		game->board->hei++;
		str = so_long_strjoin(str, line);
		line = get_next_line(fd);
		if (line != 0 && (int)ft_strlen(line) - 1 != game->board->wid)
			error_exitor("uncompleted map");
	}
	check_validate_board(game, str);
	game->board->map = ft_split(str, '\n');
	map_check(game, str);
	map_read_end(str, line, fd);
}

void	check_exit(t_game *game)
{
	if (game->board->collectible == 0)
	{
		game->board->map[game->exit_x][game->exit_y] = 'E';
		mpitw(game, game->exit_open, \
				game->exit_y * WIDTH, game->exit_x * HEIGHT);
	}
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
}
