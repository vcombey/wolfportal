/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 22:47:55 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 23:07:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	trace_portail_step_y(int portal, int draw_start, int draw_end, int x, int y, int texx)
{
	int		color;

	if (portal == 3)
	{
		if ((color = ft_pixelget(texx, (y - draw_start) * portal_blue()->height / (draw_end - draw_start), *portal_blue())) == 0x00ff00)
		{
			color = ft_pixelget(texx, (y - draw_start) * WALL_P_HEIGHT / (draw_end - draw_start), *texture());
			if (env()->side == 1)
				color = (color >> 1) & 8355711;
		}
		if (ft_pixelget_img(x, y) == 0x0)
			ft_pixelput(x, y, color);
	}
	else
	{
		if ((color = ft_pixelget(texx, (y - draw_start) * portal_blue()->height / (draw_end - draw_start), *portal_red())) == 0x00ff00)
		{
			color = ft_pixelget(texx, (y - draw_start) * WALL_P_HEIGHT  / (draw_end - draw_start), *texture());
			if (env()->side == 1)
				color = (color >> 1) & 8355711;
		}
		if (ft_pixelget_img(x, y) == 0x0)
			ft_pixelput(x, y, color);
	}
}

void	trace_portail(int x, double dist_wall, int portal)
{
	int		lineheight;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		texx;
	int		y;

	lineheight = (int)((SCREEN_HEIGHT / dist_wall) * 1.5);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (env()->side == 0)
		wallx = cam()->pos.y + dist_wall * env()->ray_dir.y;
	else
		wallx = cam()->pos.x + dist_wall * env()->ray_dir.x;
	wallx -= (int)wallx;
	texx = (int)(wallx * (double)portal_blue()->width);
	if (env()->side == 0 && env()->ray_dir.x > 0)
		texx = portal_blue()->width - texx - 1;
	if (env()->side == 1 && env()->ray_dir.y < 0)
		texx = portal_blue()->width - texx - 1;
	y = (draw_start < 0) ? 0 : draw_start;
	while (y < SCREEN_HEIGHT && y < draw_end)
	{
		trace_portail_step_y(portal, draw_start, draw_end, x, y, texx);
		y++;
	}
}
