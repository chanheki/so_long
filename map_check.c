/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:11:51 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 21:34:24 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

// static void	dfs(int x, int y, char **map, t_board *checker)
// {
// 	int			i;
// 	const int	dx[4] = {1, -1, 0, 0};
// 	const int	dy[4] = {0, 0, 1, -1};

// 	if (checker->map[x][y] == '1')
// 		return ;
// 	checker->map[x][y] = '1';
// 	if (map[x][y] == '1')
// 		return ;
// 	else if (map[x][y] == 'E')
// 		checker->map_exit -= 1;
// 	else if (map[x][y] == 'C')
// 		checker->collectible -= 1;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (x + dx[i] < checker->hei && y + dy[i] < checker->wid)
// 			dfs(x + dx[i], y + dy[i], map, checker);
// 		i++;
// 	}
// }

static int	is_cat_escape(t_game *game)
{
	// int		i;
	// int		j;
	// t_board	*checker;

	// checker = malloc(sizeof(t_board));
	// ft_memmove(checker, game->board, sizeof(game->board));
	// i = -1;
	// while (++i < game->board->hei)
	// {
	// 	j = -1;
	// 	while (++j < game->board->wid)
	// 		if (game->board->map[i][j] == 'P')
	// 			dfs(i, j, game->board->map, checker);
	// }
	// if (checker->map_exit != 0 || checker->collectible != 0)
	// 	return (1);
	// i = -1;
	// while (++i < game->board->hei)
	// 	free(checker->map[i]);
	// free(checker);
	(void)game;
	return (0);
}

static int	check_around_wall(t_game *game, char *str)
{
//	int	i;
//
//	i = 0;
	// while (str[i])
	// {
	// 	if (i <= game->board->wid)
	// 		if (str[i] != '1')
	// 			return (1);
	// 	if (i % (game->board->wid) == 0)
	// 	{
	// 		if (str[i] != '1')
	// 			return (1);
	// 		else if (str[i + game->board->wid - 1] != '1')
	// 			return (1);
	// 	}
	// 	if (i >= game->board->wid * (game->board->hei - 1))
	// 		if (str[i] != '1')
	// 			return (1);
	// 	i++;
	// }
	(void) game;
	(void) str;
	return (0);
}

static void	map_check(t_game *game, char *str)
{
	int	strlen;

	strlen = (int)ft_strlen(str);
	if (game->board->hei == game->board->wid)
		ret_error("The map must be rectangular.");
	else if (game->board->wid * game->board->hei != strlen - game->board->hei)
		ret_error("uncompleted map");
	else if (check_around_wall(game, str))
		ret_error("The map must be closed/surrounded by walls.");
	else if (is_cat_escape(game))
		ret_error("You have to check if there`s a valid path in the map.");
}

void	check_validate_board(t_game *game, char *str)
{
	int	i;
	int	player;
	int	map_exit;

	i = 0;
	player = 1;
	map_exit = 1;
	while (str[i])
	{
		if (str[i] == 'C')
			game->board->collectible ++;
		else if (str[i] == 'P')
			player --;
		else if (str[i] == 'E')
			map_exit --;
		else if (str[i] == 'e')
			game->board->enemy_count ++;
		else if (str[i] != '0' && str[i] != '1' && str[i] != '\n')
			ret_error("unexpected input on map");
		i++;
	}
	if (player || map_exit || !game->board->collectible)
		ret_error("must contain 1 exit, at least 1 collectible, \
					and 1 starting position");
	game->board->count_move = 0;
	map_check(game, str);
}
