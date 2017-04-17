/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:59:32 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/17 14:50:34 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"

double	ft_dda(t_double_pos side_dist, t_double_pos delta_dist, t_int_pos step,
		t_double_pos ray_dir, int x)
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
		if (env()->map[env()->wall.x][env()->wall.y] == 3)
		{
			trace_portail(x, (env()->side == 0) ? side_dist.x : side_dist.y, 0xFF8C00);
			env()->wall.x = env()->blue.x;
			env()->wall.y = env()->blue.y - 1;
		}
		else if (env()->map[env()->wall.x][env()->wall.y] == 4)
		{
			trace_portail(x, (env()->side == 0) ? side_dist.x : side_dist.y, 0x00BFFF);
			env()->wall.x = env()->red.x;
			env()->wall.y = env()->red.y + 1;
		}
		else if (env()->map[env()->wall.x][env()->wall.y] == 1)
			hit = 1;
	}
	(void)ray_dir;
	return (env()->side == 0) ? side_dist.x : side_dist.y;
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
