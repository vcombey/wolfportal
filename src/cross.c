/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:32:25 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/25 14:26:49 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_rect(int x1, int y1, int x2, int y2)
{
	int i;
	int j;

	i = x1;
	while (i  < x2)
	{
		j = y1;
		while (j < y2)
		{
			ft_pixelput(j, i, 0xFFFFFF);	
			j++;
		}
		i++;
	}
}


void	cross()
{
	t_int_pos mid;

	mid.x = SCREEN_HEIGHT / 2;
	mid.y = SCREEN_WIDTH / 2;
	draw_rect(mid.x - 5, mid.y - 20, mid.x + 5, mid.y + 20);
	draw_rect(mid.x - 20, mid.y - 5, mid.x + 20, mid.y + 5);
}
