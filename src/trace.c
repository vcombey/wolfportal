/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 20:35:01 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/17 15:06:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_trace_textur(int x, double dist_wall,
		int draw_start, int draw_end)
{
	double			wallx;
	unsigned int	color;
	int				texx;
	int				y;

	if (env()->side == 0)
		wallx = cam()->pos.y + dist_wall * env()->ray_dir.y;
	else
		wallx = cam()->pos.x + dist_wall * env()->ray_dir.x;
	wallx -= (int)wallx;
	texx = (int)(wallx * (double)100);
	if (env()->side == 0 && env()->ray_dir.x > 0)
		texx = 100 - texx - 1;
	if (env()->side == 1 && env()->ray_dir.y < 0)
		texx = 100 - texx - 1;
	y = draw_start;
	while (y < draw_end)
	{
		color = ft_pixelget(texx, (y - draw_start) *
				100 / (draw_end - draw_start));
		if (env()->side == 1)
			color = (color >> 1) & 8355711;
		ft_pixelput(x, y, color);
		y++;
	}
}

void		ft_trace_colone(int x, double dist_wall)
{
	int	lineheight;
	int	draw_start;
	int	draw_end;
	int	p;

	lineheight = (int)(SCREEN_HEIGHT / dist_wall);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	p = draw_start;
	ft_trace_textur(x, dist_wall, draw_start, draw_end);
	//floor_casting(x, dist_wall, draw_end);
}

void	trace_portail(int x, double dist_wall, int color)
{
	int	lineheight;
	int	draw_start;
	int	draw_end;
	double			wallx;
	int				texx;
	int				y;


	lineheight = (int)(SCREEN_HEIGHT / dist_wall);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	ft_pixelput(x, draw_start, color);
	ft_pixelput(x, draw_end, color);
	if (env()->side == 0)
		wallx = cam()->pos.y + dist_wall * env()->ray_dir.y;
	else
		wallx = cam()->pos.x + dist_wall * env()->ray_dir.x;
	wallx -= (int)wallx;
	texx = (int)(wallx * (double)100);
	if (env()->side == 0 && env()->ray_dir.x > 0)
		texx = 100 - texx - 1;
	if (env()->side == 1 && env()->ray_dir.y < 0)
		texx = 100 - texx - 1;
	y = draw_start;
	if (texx == 0 || texx == 100)
	{
		while (y < draw_end)
		{
			ft_pixelput(x, y, color);
			y++;
		}
	}
}
