/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 12:31:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/27 15:40:25 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include <stdio.h>
#include "libft.h"

static void	ft_turn(void)
{
	double old_dirx;
	double old_planex;

	if (key()->left)
	{
		old_dirx = cam()->dir.x;
		cam()->dir.x = cam()->dir.x * cos(0.04) - cam()->dir.y * sin(0.04);
		cam()->dir.y = old_dirx * sin(0.04) + cam()->dir.y * cos(0.04);
		old_planex = cam()->plane.x;
		cam()->plane.x = cam()->plane.x * cos(0.04) - cam()->plane.y *
			sin(0.04);
		cam()->plane.y = old_planex * sin(0.04) + cam()->plane.y * cos(0.04);
	}
	if (key()->right)
	{
		old_dirx = cam()->dir.x;
		cam()->dir.x = cam()->dir.x * cos(-0.04) - cam()->dir.y * sin(-0.04);
		cam()->dir.y = old_dirx * sin(-0.04) + cam()->dir.y * cos(-0.04);
		old_planex = cam()->plane.x;
		cam()->plane.x = cam()->plane.x * cos(-0.04)
			- cam()->plane.y * sin(-0.04);
		cam()->plane.y = old_planex * sin(-0.04) + cam()->plane.y * cos(-0.04);
	}
}

void		ft_move(void)
{
	int		portal;

	if (key()->up)
	{
		if ((portal = env()->map[(int)(cam()->pos.x + cam()->dir.x * 0.1)]
					[(int)(cam()->pos.y + cam()->dir.y * 0.1)]) >= 3)
			teleport_pos(portal);
		if (env()->map[(int)(cam()->pos.x + cam()->dir.x * 0.1)]
				[(int)cam()->pos.y] <= 0)
			cam()->pos.x += cam()->dir.x * 0.1;
		if (env()->map[(int)cam()->pos.x]
				[(int)(cam()->pos.y + cam()->dir.y * 0.1)] <= 0)
			cam()->pos.y += cam()->dir.y * 0.1;
	}
	if (key()->down)
	{
		if (env()->map[(int)(cam()->pos.x - cam()->dir.x * 0.1)]
				[(int)cam()->pos.y] <= 0)
			cam()->pos.x -= cam()->dir.x * 0.1;
		if (env()->map[(int)cam()->pos.x]
				[(int)(cam()->pos.y - cam()->dir.y * 0.1)] <= 0)
			cam()->pos.y -= cam()->dir.y * 0.1;
	}
}

int			recalc_img(void *param)
{
	(void)param;
	ft_move();
	ft_turn();
	tourelle_shoot();
	ft_memset(env()->ptr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	ft_wolf();
	cross();
	draw_portal_gun();
	mlx_put_image_to_window(env()->mlx, env()->win, env()->img, 0, 0);
	return (0);
}
