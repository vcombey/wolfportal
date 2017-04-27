/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tourelle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:53:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/27 15:27:56 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>
	#include <stdio.h>

void	trace_tourelle_step_y(int tourelle_y, int x, int y, int texx)
{
	int		color;

	if (((color = ft_pixelget(texx, tourelle_y, *tourelle())) != 0x00ff00) && (ft_pixelget_img(x, y) == 0x0))
		ft_pixelput(x, y, color);
}

void	draw_tourelle(int x, double dist_wall)
{
	int		lineheight;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		texx;
	int		y;

	lineheight = (int)((SCREEN_HEIGHT / dist_wall) / 3);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (env()->side == 0)
		wallx = cam()->pos.y + dist_wall * env()->ray_dir.y;
	else
		wallx = cam()->pos.x + dist_wall * env()->ray_dir.x;
	wallx -= (int)wallx;
	texx = (int)(wallx * (double)tourelle()->width);
	if (env()->side == 0 && env()->ray_dir.x > 0)
		texx = tourelle()->width - texx - 1;
	if (env()->side == 1 && env()->ray_dir.y < 0)
		texx = tourelle()->width - texx - 1;
	y = (draw_start < 0) ? 0 : draw_start;
	while (y < SCREEN_HEIGHT && y < draw_end)
	{
		trace_tourelle_step_y((y - draw_start) * tourelle()->height / (draw_end - draw_start), x, y, texx);
		y++;
	}
}

t_texture	*tourelle(void)
{
	static t_texture	t;

	return (&t);
}

void	tourelle_shoot(void)
{
	if ((env()->map[(int)cam()->pos.x][(int)cam()->pos.y]) == -1)
		env()->life--;
	printf("live:%d",env()->life);
	if (env()->life == 0)
		exit(0);
}
