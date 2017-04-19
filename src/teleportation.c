/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:19:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/19 12:22:14 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

void	teleport_rot(int portal)
{
	int		a;
	int		b;
	double	tmp;

	if (env()->sideblue == env()->sidered)
	{
		if (ft_abs(env()->sideblue == 1))
			cam()->dir.x *= -1;
		else
			cam()->dir.y *= -1;
	}
	else if (ft_abs(env()->sideblue) != ft_abs(env()->sidered))
	{
		if (portal == 3)
		{
			a = transform_sidecolor(env()->sidered);
			b = transform_sidecolor(env()->sideblue);
		}
		else
		{
			b = transform_sidecolor(env()->sidered);
			a = transform_sidecolor(env()->sideblue);
		}
		if (a < b || (a == 4 && b == 1))
		{
			tmp = cam()->dir.y;
			cam()->dir.y = -cam()->dir.x;
			cam()->dir.x = tmp;
		}
		else if (a > b || (a == 1 && b == 4))
		{
			tmp = -cam()->dir.y;
			cam()->dir.y = cam()->dir.x;
			cam()->dir.x = tmp;
		}
	}
}

void	teleport_pos(int portal)
{
	if (portal == 3)
	{
		cam()->pos.x = (double)env()->blue.x;
		cam()->pos.y = (double)env()->blue.y;
		if (ft_abs(env()->sideblue) == 1)
			cam()->pos.x -= (double)env()->sideblue;
		else
			cam()->pos.y -= (double)env()->sideblue / 2;
		teleport_rot(portal);
		cam()->pos.x += cam()->dir.x * 0.1;
		cam()->pos.y += cam()->dir.y * 0.1;
	}
	else if (portal == 4)
	{
		cam()->pos.x = (double)env()->red.x;
		cam()->pos.y = (double)env()->red.y;
		if (ft_abs(env()->sidered) == 1)
			cam()->pos.x -= (double)env()->sidered;
		else
			cam()->pos.y -= (double)env()->sidered / 2;
		teleport_rot(portal);
		cam()->pos.x += cam()->dir.x * 0.1;
		cam()->pos.y += cam()->dir.y * 0.1;
	}
}
//&& good_side_portal(step, env()->sidered))
//&& good_side_portal(step, env()->sideblue))
