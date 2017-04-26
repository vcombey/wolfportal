/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:59:32 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 12:27:38 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"
#include "libft.h"
#include <stdio.h>

int		ft_hit(double proj, int portal, t_dda dda)
{
	if (portal == 3 && good_side_portal((dda.step), env()->sidered))
	{
		trace_portail(dda.x, (env()->side == 0) ? (dda.side_dist)->x / proj: (dda.side_dist)->y / proj, portal);
		env()->wall.x = env()->blue.x;
		env()->wall.y = env()->blue.y;
		if (ft_abs(env()->sideblue) == 1)
			env()->wall.x -= env()->sideblue;
		else
			env()->wall.y -= (env()->sideblue / 2);
		transform_direction_ray_portal(portal, dda);
		return (0);
	}
	else if (portal == 4 && good_side_portal((dda.step), env()->sideblue))
	{
		trace_portail(dda.x, (env()->side == 0) ? (dda.side_dist)->x / proj : (dda.side_dist)->y / proj, portal);
		env()->wall.x = env()->red.x;
		env()->wall.y = env()->red.y;
		if (ft_abs(env()->sidered) == 1)
			env()->wall.x -= env()->sidered;
		else
			env()->wall.y -= (env()->sidered / 2);
		transform_direction_ray_portal(portal, dda);
		return (0);
	}
	else if (portal == 2)
		return (0);
	return (1);
}


double	ft_dda(t_dda dda)
{
	int hit;
	int	portal;
	double proj;

	hit = 0;
	proj = sqrt((((dda.ray_dir)->y * (dda.ray_dir)->y) + ((dda.ray_dir)->x * (dda.ray_dir)->x)));
	env()->wall.x = (int)cam()->pos.x;
	env()->wall.y = (int)cam()->pos.y;
	while (hit == 0)
	{
		if ((dda.side_dist)->x < (dda.side_dist)->y && ((portal = env()->map[env()->wall.x + (dda.step)->x][env()->wall.y]) > 0))
		{
			env()->side = 0;
			hit = ft_hit(proj, portal, dda);
		}
		else if ((dda.side_dist)->y < (dda.side_dist)->x && ((portal = env()->map[env()->wall.x][env()->wall.y + (dda.step)->y]) > 0))
		{
			env()->side = 1;
			hit = ft_hit(proj, portal, dda);
		}
		else if ((dda.side_dist)->x <= (dda.side_dist)->y)
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
		//printf("wallx->%d, wally->%d\n", env()->wall.x, env()->wall.y);
		//printf("(dda.side_dist)x->%f, (dda.side_dist)y->%f\n", (dda.side_dist)->x, (dda.side_dist)->y);
		//printf("(dda.step)x->%d, (dda.step)y->%d\n", (dda.step)->x, (dda.step)->y);
		//usleep(1);
	}
	return (env()->side == 0) ? (dda.side_dist)->x / proj : (dda.side_dist)->y / proj;
	/*
	   return (env()->side == 0) ? ((env()->wall.x - cam()->pos.x + (1 - (dda.step).x) /
	   2) / (dda.ray_dir).x) : ((env()->wall.y - cam()->pos.y + (1 - (dda.step).y)
	   / 2) / (dda.ray_dir).y);
	   */
}

void	ft_init_dist(t_dda dda)
{
	if ((dda.ray_dir)->x < 0)
	{
		(dda.side_dist)->x = (cam()->pos.x - (int)cam()->pos.x) * (dda.delta_dist)->x;
		(dda.step)->x = -1;
	}
	else
	{
		(dda.side_dist)->x = ((int)cam()->pos.x + 1.0 - cam()->pos.x) * (dda.delta_dist)->x;
		(dda.step)->x = 1;
	}
	if ((dda.ray_dir)->y < 0)
	{
		(dda.step)->y = -1;
		(dda.side_dist)->y = (cam()->pos.y - (int)cam()->pos.y) * (dda.delta_dist)->y;
	}
	else
	{
		(dda.step)->y = 1;
		(dda.side_dist)->y = ((int)cam()->pos.y + 1.0 - cam()->pos.y) * (dda.delta_dist)->y;
	}
}

double	ft_calc_dist(int x, t_dda dda)
{
	double			range;

	range = 2 * (double)x / (double)SCREEN_WIDTH - 1;
	(dda.ray_dir)->x = cam()->dir.x + range * cam()->plane.x;
	(dda.ray_dir)->y = cam()->dir.y + range * cam()->plane.y;
	dda.x = x;
	env()->ray_dir.x = (dda.ray_dir)->x;
	env()->ray_dir.y = (dda.ray_dir)->y;
	(dda.delta_dist)->x = sqrt(1 + (env()->ray_dir.y * env()->ray_dir.y) /
			(env()->ray_dir.x * env()->ray_dir.x));
	(dda.delta_dist)->y = sqrt(1 + (env()->ray_dir.x * env()->ray_dir.x) /
			(env()->ray_dir.y * env()->ray_dir.y));
	ft_init_dist(dda);
	return (ft_dda(dda));
}

void	ft_wolf(void)
{
	int				x;
	double			dist_wall;
	t_dda			dda;
	t_double_pos	ray_dir;
	t_double_pos	side_dist;
	t_double_pos	delta_dist;
	t_int_pos		step;

	dda.ray_dir = &ray_dir;
	dda.side_dist = &side_dist;
	dda.delta_dist = &delta_dist;
	dda.step = &step;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		dist_wall = ft_calc_dist(x, dda);
		//printf("dist_wall->%f\n", dist_wall);
		ft_trace_colone(x, dist_wall, *(dda.ray_dir));
		x++;
	}
}
