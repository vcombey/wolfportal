/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixelget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 20:00:04 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/04 19:30:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "wolf.h"

unsigned int		ft_pixelget(int x, int y)
{
	int				dest;

	if (y < 0 || x < 0)
		return (0);
	dest = y * texture()->size_line + x * (texture()->bpp / 8);
	if ((100 * 100 * (texture()->bpp / 8)) <= dest)
		return (0);
	if (dest < 0)
		return (0);
	return (*(unsigned int *)(&texture()->ptr[dest]));
}
