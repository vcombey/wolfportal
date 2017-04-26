/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal_gun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:49:16 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 14:53:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

unsigned int		ft_pixelget_gun(int x, int y)
{
	int				dest;

	if (y < 0 || x < 0)
		return (0);
	dest = y * gun()->size_line + x * (gun()->bpp / 8);
	if ((PORTAL_GUN_HEIGHT * PORTAL_GUN_WIDTH * (gun()->bpp / 8)) <= dest)
		return (0);
	if (dest < 0)
		return (0);
	return (*(unsigned int *)(&gun()->ptr[dest]));
}

void				draw_portal_gun(void)
{
	double			y;
	double			x;
	unsigned int	color;

	y = 2 * SCREEN_HEIGHT / 3;
	x = SCREEN_WIDTH / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = SCREEN_WIDTH / 2;
		while (x < SCREEN_WIDTH)
		{
			if ((color = ft_pixelget((x / (SCREEN_WIDTH / 2) - 1) *
			PORTAL_GUN_WIDTH, ((y - (2 * SCREEN_HEIGHT / 3)) /
			(SCREEN_HEIGHT / 3)) * PORTAL_GUN_HEIGHT, *gun()))
			< 0xFFFFFF)
				ft_pixelput(x, y, color);
			x++;
		}
		y++;
	}
}
