/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 08:59:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 12:27:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

void	change_portail(int keycode)
{
	if (keycode == KEY_Z)
	{
		env()->map[env()->red.x][env()->red.y] = 1;
		env()->map[env()->wall.x][env()->wall.y] = 3;
		env()->red.x = env()->wall.x;
		env()->red.y = env()->wall.y;
		if (env()->side == 0 && cam()->dir.x >= 0)
			env()->sidered = 1;
		else if (env()->side == 0 && cam()->dir.x < 0)
			env()->sidered = -1;
		else if (env()->side == 1 && cam()->dir.y >= 0)
			env()->sidered = 2;
		else if (env()->side == 1 && cam()->dir.y < 0)
			env()->sidered = -2;
	}
	else if (keycode == KEY_S)
	{
		env()->map[env()->blue.x][env()->blue.y] = 1;
		env()->map[env()->wall.x][env()->wall.y] = 4;
		env()->blue.x = env()->wall.x;
		env()->blue.y = env()->wall.y;
		if (env()->side == 0 && cam()->dir.x >= 0)
			env()->sideblue = 1;
		else if (env()->side == 0 && cam()->dir.x < 0)
			env()->sideblue = -1;
		else if (env()->side == 1 && cam()->dir.y >= 0)
			env()->sideblue = 2;
		else if (env()->side == 1 && cam()->dir.y < 0)
			env()->sideblue = -2;
	}
}

void	ft_shoot(t_dda dda, int keycode)
{
	int hit;

	hit = 0;
	env()->wall.x = (int)cam()->pos.x;
	env()->wall.y = (int)cam()->pos.y;
	while (hit == 0)
	{
		if ((dda.side_dist)->x < (dda.side_dist)->y)
		{
			(dda.side_dist)->x += (dda.delta_dist)->x;
			env()->wall.x += (dda.step)->x;
			env()->side = 0;
		}
		else
		{
			(dda.side_dist)->y += (dda.delta_dist)->y;
			env()->wall.y += (dda.step)->y;
			env()->side = 1;
		}
		if ((env()->map[env()->wall.x][env()->wall.y]) > 0)
			hit = 1;
	}
	change_portail(keycode);
}

void	portal_gun_shoot(int keycode)
{
	t_dda			dda;
	t_double_pos	ray_dir;
	t_double_pos	side_dist;
	t_double_pos	delta_dist;
	t_int_pos		step;

	dda.ray_dir = &ray_dir;
	dda.side_dist = &side_dist;
	dda.delta_dist = &delta_dist;
	dda.step = &step;
	(dda.delta_dist)->x = sqrt(1 + (cam()->dir.y * cam()->dir.y) /
			(cam()->dir.x * cam()->dir.x));
	(dda.delta_dist)->y = sqrt(1 + (cam()->dir.x * cam()->dir.x) /
			(cam()->dir.y * cam()->dir.y));
	(dda.ray_dir)->x = cam()->dir.x;
	(dda.ray_dir)->y = cam()->dir.y;
	ft_init_dist(dda);
	return (ft_shoot(dda, keycode));
}

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

void	draw_portal_gun()
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
			if ((color = ft_pixelget_gun((x / (SCREEN_WIDTH / 2) - 1) * PORTAL_GUN_WIDTH, ((y - (2 * SCREEN_HEIGHT / 3))/ (SCREEN_HEIGHT / 3)) * PORTAL_GUN_HEIGHT)) < 0xFFFFFF)
				ft_pixelput(x, y, color);
			x++;
		}
		y++;

	}
}
