/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 20:35:01 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/26 14:52:50 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_trace_textur(int x, double dist_wall,
		int draw_start, int draw_end, t_double_pos ray_dir)
{
	double			wallx;
	unsigned int	color;
	int				texx;
	int				y;

	if (env()->side == 0)
		wallx = cam()->pos.y + dist_wall * ray_dir.y;
	else
		wallx = cam()->pos.x + dist_wall * ray_dir.x;
	wallx -= (int)wallx;
	texx = (int)(wallx * (double)WALL_p_WIDTH);
	if (env()->side == 0 && ray_dir.x > 0)
		texx = WALL_p_WIDTH - texx - 1;
	if (env()->side == 1 && ray_dir.y < 0)
		texx = WALL_p_WIDTH - texx - 1;
	y = draw_start;
	while (y < draw_end)
	{
		color = ft_pixelget(texx, (y - draw_start) *
				WALL_p_HEIGHT / (draw_end - draw_start), *texture());
		if (env()->side == 1)
			color = (color >> 1) & 8355711;
		if (ft_pixelget_img(x, y) == 0x0)
			ft_pixelput(x, y, color);
		y++;
	}
}

void		ft_trace_colone(int x, double dist_wall, t_double_pos ray_dir)
{
	int	lineheight;
	int	draw_start;
	int	draw_end;
	int	p;

	lineheight = (int)((SCREEN_HEIGHT / dist_wall) * 1.5);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	p = draw_start;
	ft_trace_textur(x, dist_wall, draw_start, draw_end, ray_dir);
}

void	trace_portail(int x, double dist_wall, int portal)
{
	int		lineheight;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		texx;
	int		color;
	int		y;


	lineheight = (int)((SCREEN_HEIGHT / dist_wall) * 1.5);
	draw_start = -lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineheight / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
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
	y = draw_start;
	while (y < draw_end)
	{
		if (portal == 3)
		{
			if ((color = ft_pixelget(texx, (y - draw_start) * portal_blue()->height / (draw_end - draw_start), *portal_blue())) == 0x00ff00)
			{
				color = ft_pixelget(texx, (y - draw_start) * WALL_p_HEIGHT / (draw_end - draw_start), *texture());
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
				color = ft_pixelget(texx, (y - draw_start) * WALL_p_HEIGHT  / (draw_end - draw_start), *texture());
				if (env()->side == 1)
					color = (color >> 1) & 8355711;
			}
			if (ft_pixelget_img(x, y) == 0x0)
				ft_pixelput(x, y, color);
		}
		y++;
	}
}
