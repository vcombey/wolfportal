/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tourelle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:53:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/27 16:56:39 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	trace_tourelle_step_y(int tourelle_y, int x, int y, int texx)
{
	unsigned int		color;

	if (((color = ft_pixelget(texx, tourelle_y, *tourelle())) != 0xFF000000) && (ft_pixelget_img(x, y) == 0x0))
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

	lineheight = (int)((SCREEN_HEIGHT / dist_wall) *1.5);
	draw_start = SCREEN_HEIGHT / 2;
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
	int		x;
	int		y;
	if ((env()->map[(int)cam()->pos.x][(int)cam()->pos.y]) == -1)
	{
		env()->life--;
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			x = 0;
			while (x < SCREEN_WIDTH)
			{
				ft_pixelput(x, y, 0xF0FF0000);
				x++;
			}
			y++;
		}

	}
	if (env()->life == 0)
	{
		ft_putstr("GAME OVER\n");
		exit(0);
	}
}
