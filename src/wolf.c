/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:59:32 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/19 18:05:47 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"
#include "libft.h"
#include <stdio.h>

int		good_side_portal(t_int_pos *step, int side_color)
{
	if (env()->side == 0 && ft_abs(side_color) == 1 && side_color == step->x)
		return (1);
	else if (env()->side == 1 && ft_abs(side_color) == 2 && side_color == 2 * step->y)
		return (1);
	return (0);
}

int		transform_sidecolor(int side_color)
{
	if (side_color < 0)
		return ((side_color == -1) ? 3 : 4);
	return side_color;
}

void	transform_direction_ray_portal(int portal, t_int_pos *step, t_double_pos *delta_dist)
{
	int		a;
	int		b;
	int		new_stepx;
	//double	tmp;

	(void)delta_dist;
	if (env()->sideblue == env()->sidered)
	{
		if (env()->side == 0)
			step->x *= -1;
		else
			step->y *= -1;
	}
	else if (ft_abs(env()->sideblue) != ft_abs(env()->sidered))
	{
		//tmp = delta_dist->x;
		//delta_dist->x = delta_dist->y;
		//delta_dist->y = tmp;
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
			new_stepx = -step->y;
			step->y = step->x;
			step->x = new_stepx;
		}
		else if (a > b || (a == 1 && b == 4))
		{
			new_stepx = step->y;
			step->y = -step->x;
			step->x = new_stepx;
		}
	}
}

int		ft_hit(int x, double proj, int portal, t_int_pos *step, t_double_pos side_dist, t_double_pos *delta_dist)
{
	if (portal == 3 && good_side_portal(step, env()->sidered))
	{
		trace_portail(x, (env()->side == 0) ? side_dist.x / proj: side_dist.y / proj, 0xFF8C00);
		env()->wall.x = env()->blue.x;
		env()->wall.y = env()->blue.y;
		if (ft_abs(env()->sideblue) == 1)
			env()->wall.x -= env()->sideblue;
		else
			env()->wall.y -= (env()->sideblue / 2);
		transform_direction_ray_portal(portal, step, delta_dist);
		return (0);
	}
	else if (portal == 4 && good_side_portal(step, env()->sideblue))
	{
		trace_portail(x, (env()->side == 0) ? side_dist.x / proj : side_dist.y / proj, 0x00BFFF);
		env()->wall.x = env()->red.x;
		env()->wall.y = env()->red.y;
		if (ft_abs(env()->sidered) == 1)
			env()->wall.x -= env()->sidered;
		else
			env()->wall.y -= (env()->sidered / 2);
		transform_direction_ray_portal(portal, step, delta_dist);
		return (0);
	}
	return (1);
}

double	ft_dda(t_double_pos side_dist, t_double_pos delta_dist, t_int_pos step,
		t_double_pos ray_dir, int x)
{
	int hit;
	int	portal;
	double proj;

	hit = 0;
	proj = sqrt(((ray_dir.y * ray_dir.y) + (ray_dir.x * ray_dir.x)));
	env()->wall.x = (int)cam()->pos.x;
	env()->wall.y = (int)cam()->pos.y;
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y && ((portal = env()->map[env()->wall.x + step.x][env()->wall.y]) > 0))
		{
			env()->side = 0;
			hit = ft_hit(x, proj, portal, &step, side_dist, &delta_dist);
		}
		else if (side_dist.y < side_dist.x && ((portal = env()->map[env()->wall.x][env()->wall.y + step.y]) > 0))
		{
			env()->side = 1;
			hit = ft_hit(x, proj, portal, &step, side_dist, &delta_dist);
		}
		else if (side_dist.x < side_dist.y)
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
	}
	return (env()->side == 0) ? side_dist.x / proj : side_dist.y / proj;
	/*
	   return (env()->side == 0) ? ((env()->wall.x - cam()->pos.x + (1 - step.x) /
	   2) / ray_dir.x) : ((env()->wall.y - cam()->pos.y + (1 - step.y)
	   / 2) / ray_dir.y);
	   */
}

void	ft_init_dist(t_double_pos *ray_dir, t_double_pos *side_dist,
		t_double_pos *delta_dist, t_int_pos *step)
{
	if (ray_dir->x < 0)
	{
		side_dist->x = (cam()->pos.x - (int)cam()->pos.x) * delta_dist->x;
		step->x = -1;
	}
	else
	{
		side_dist->x = ((int)cam()->pos.x + 1.0 - cam()->pos.x) * delta_dist->x;
		step->x = 1;
	}
	if (ray_dir->y < 0)
	{
		step->y = -1;
		side_dist->y = (cam()->pos.y - (int)cam()->pos.y) * delta_dist->y;
	}
	else
	{
		step->y = 1;
		side_dist->y = ((int)cam()->pos.y + 1.0 - cam()->pos.y) * delta_dist->y;
	}
}

double	ft_calc_dist(int x)
{
	double			range;
	t_double_pos	delta_dist;
	t_int_pos		step;
	t_double_pos	side_dist;

	range = 2 * (double)x / (double)SCREEN_WIDTH - 1;
	env()->ray_dir.x = cam()->dir.x + range * cam()->plane.x;
	env()->ray_dir.y = cam()->dir.y + range * cam()->plane.y;
	delta_dist.x = sqrt(1 + (env()->ray_dir.y * env()->ray_dir.y) /
			(env()->ray_dir.x * env()->ray_dir.x));
	delta_dist.y = sqrt(1 + (env()->ray_dir.x * env()->ray_dir.x) /
			(env()->ray_dir.y * env()->ray_dir.y));
	ft_init_dist(&env()->ray_dir, &side_dist, &delta_dist, &step);
	return (ft_dda(side_dist, delta_dist, step, env()->ray_dir, x));
}

void	ft_wolf(void)
{
	int		x;
	double	dist_wall;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		dist_wall = ft_calc_dist(x);
		ft_trace_colone(x, dist_wall);
		x++;
	}
}
