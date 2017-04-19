/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 08:59:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/19 14:29:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <stdio.h>

void	change_portail(int keycode) {
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

void	ft_shoot(t_double_pos side_dist, t_double_pos delta_dist, t_int_pos step, int keycode)
{
	int hit;

	hit = 0;
	env()->wall.x = (int)cam()->pos.x;
	env()->wall.y = (int)cam()->pos.y;
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			env()->wall.x += step.x;
			env()->side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			env()->wall.y += step.y;
			env()->side = 1;
		}
		if ((env()->map[env()->wall.x][env()->wall.y]) > 0)
			hit = 1;
		//printf("wallx-> %d\n", env()->wall.x);
	}
	change_portail(keycode);
}

void	portal_gun_shoot(int keycode)
{
	t_double_pos	delta_dist;
	t_int_pos		step;
	t_double_pos	side_dist;

	delta_dist.x = sqrt(1 + (cam()->dir.y * cam()->dir.y) /
			(cam()->dir.x * cam()->dir.x));
	delta_dist.y = sqrt(1 + (cam()->dir.x * cam()->dir.x) /
			(cam()->dir.y * cam()->dir.y));
	ft_init_dist(&cam()->dir, &side_dist, &delta_dist, &step);
	return (ft_shoot(side_dist, delta_dist, step, keycode));
}
