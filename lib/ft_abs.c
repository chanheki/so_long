/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:07:20 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/21 23:07:57 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}