/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:11:51 by chanheki          #+#    #+#             */
/*   Updated: 2023/01/17 19:42:50 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	dfs(int x, int y, char **map, t_board *checker)
{
	int			i;
	const int	dx[4] = {1, -1, 0, 0};
	const int	dy[4] = {0, 0, 1, -1};

	if (checker->map[x][y] == '1')
		return ;
	checker->map[x][y] = '1';
	if (map[x][y] == '1')
		return ;
	else if (map[x][y] == 'E')
		checker->map_exit -= 1;
	else if (map[x][y] == 'C')
		checker->collectible -= 1;
	i = 0;
	while (i < 4)
	{
		if (x + dx[i] < checker->hei && y + dy[i] < checker->wid)
			dfs(x + dx[i], y + dy[i], map, checker);
		i++;
	}
}

static int	escape_checker(t_game *game, char *str)
{
	int		i;
	int		j;
	t_board	*checker;

	(void) str;
	checker = malloc(sizeof(t_board));
	ft_memmove(checker, game->board, sizeof(t_board));
	checker->map = ft_split(str, '\n');
	i = -1;
	while (++i < game->board->hei)
	{
		j = -1;
		while (++j < game->board->wid)
			if (game->board->map[i][j] == 'P')
				dfs(i, j, game->board->map, checker);
	}
	if (checker->map_exit != 0 || checker->collectible != 0)
		return (1);
	i = -1;
	while (++i < game->board->hei)
		free(checker->map[i]);
	free(checker->map);
	free(checker);
	return (0);
}

static int	wall_checker(t_game *game, char *str)
{
	int	i;

	i = 0;
	while (i < (game->board->wid + 1) * (game->board->hei) - 1)
	{
		if (i < game->board->wid)
		{
			if (str[i] != '1')
				return (1);
		}
		else if (i >= (game->board->wid + 1) * (game->board->hei - 1))
		{
			if (str[i] != '1')
				return (1);
		}
		else if (str[i] == '\n')
		{
			if (str[i - 1] != '1')
				return (1);
			else if (str[i + 1] != '1')
				return (1);
		}
		i++;
	}
	return (0);
}

void	map_check(t_game *game, char *str)
{
	int	strlen;

	strlen = (int)ft_strlen(str);
	if (game->board->hei == game->board->wid)
		error_exitor("The map must be rectangular.");
	else if (wall_checker(game, str))
		error_exitor("The map must be closed/surrounded by walls.");
	else if (escape_checker(game, str))
		error_exitor("You have to check if there`s a valid path in the map.");
}

void	check_validate_board(t_game *game, char *str)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (str[i])
	{
		if (str[i] == 'C')
			game->board->collectible ++;
		else if (str[i] == 'P')
			player ++;
		else if (str[i] == 'E')
			game->board->map_exit ++;
		else if (str[i] == 'B')
			game->board->enemy_count ++;
		else if (str[i] != '0' && str[i] != '1' && str[i] != '\n')
			error_exitor("unexpected input on map");
		i++;
	}
	if (!(player == 1) || !(game->board->map_exit == 1) || \
			game->board->collectible < 1)
		error_exitor("must contain 1 exit, at least 1 collectible, \
and 1 starting position");
}
