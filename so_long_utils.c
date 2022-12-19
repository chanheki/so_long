/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:13:08 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 21:39:58 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	checkerset(t_game *checker, t_game *game)
{
	checker->board->collectible = game->board->collectible;
	checker->board->map_exit = 1;
	checker->board->hei = game->board->hei;
	checker->board->wid = game->board->wid;
	// checker->board->map = str_to_matrix(game->board->str, game->board->hei, game->board->wid);
	// game->board->map = str_to_matrix(game->board->str, game->board->hei, game->board->wid);
}

char	*solong_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
		s1 = "";
	if (!s2)
		return (NULL);
	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2 != '\n')
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	**str_to_matrix(char *str, int height, int width)
{
	char	**matrix;
	int		i;

	matrix = (char **)malloc(sizeof(char *) * (height +1));
	if (!matrix)
		ret_error("malloc failed");
	i = 0;
	while (i < height)
	{
		matrix[i] = ft_substr(str, i * width, width);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

void	ft_putnbr(int n)
{
	long long	temp;
	int			i;
	char		str[15];

	temp = (long long)n;
	i = 0;
	if (n < 0)
	{
		temp *= -1;
		write (1, "-", 1);
	}
	else if (n == 0)
	{
		write (1, "0", 1);
		return ;
	}
	while (temp)
	{
		str[i++] = (temp % 10) + '0';
		temp /= 10;
	}
	while (--i >= 0)
		write(1, str + i, 1);
}
