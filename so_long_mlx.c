/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:49:55 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 19:03:52 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	*mxfti(void *xvar, char *file, int *width, int *height)
{
	return (mlx_xpm_file_to_image(xvar, file, width, height));
}

int	mpitw(t_game *game, void *img_ptr, int x, int y)
{
	return (mlx_put_image_to_window(game->mlx, game->win, img_ptr, x, y));
}
