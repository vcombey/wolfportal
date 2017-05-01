/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 10:19:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/01 13:54:32 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

void	teleport_rot_perpendicular(int portal)
{
	int		a;
	int		b;

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
	if ((a < b && !(a == 1 && b == 4)) || (a == 4 && b == 1))
	{
		ft_rev_rot_double(&cam()->dir);
		ft_rev_rot_double(&cam()->plane);
	}
	else if (a > b || (a == 1 && b == 4))
	{
		ft_rot_double(&cam()->dir);
		ft_rot_double(&cam()->plane);
	}
}

void	teleport_rot(int portal)
{
	if (env()->sideblue == env()->sidered)
	{
		cam()->dir.x *= -1;
		cam()->dir.y *= -1;
		cam()->plane.x *= -1;
		cam()->plane.y *= -1;
	}
	else if (ft_abs(env()->sideblue) != ft_abs(env()->sidered))
		teleport_rot_perpendicular(portal);
}

void	teleport_pos_blue(int portal)
{
	cam()->pos.x = (double)env()->blue.x;
	cam()->pos.y = (double)env()->blue.y;
	if (ft_abs(env()->sideblue) == 1)
	{
		cam()->pos.x -= (double)env()->sideblue;
		cam()->pos.y += 0.5;
	}
	else
	{
		cam()->pos.y -= ((double)env()->sideblue / 2);
		cam()->pos.x += 0.5;
	}
	teleport_rot(portal);
	cam()->pos.x += cam()->dir.x * 0.1;
	cam()->pos.y += cam()->dir.y * 0.1;
}

void	teleport_pos_red(int portal)
{
	cam()->pos.x = (double)env()->red.x;
	cam()->pos.y = (double)env()->red.y;
	if (ft_abs(env()->sidered) == 1)
	{
		cam()->pos.x -= (double)env()->sidered;
		cam()->pos.y += 0.5;
	}
	else
	{
		cam()->pos.y -= ((double)env()->sidered / 2);
		cam()->pos.x += 0.5;
	}
	teleport_rot(portal);
	cam()->pos.x += cam()->dir.x * 0.1;
	cam()->pos.y += cam()->dir.y * 0.1;
}

void	teleport_pos(int portal)
{
	if (portal == 3)
		teleport_pos_blue(portal);
	else if (portal == 4)
		teleport_pos_red(portal);
}
