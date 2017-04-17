/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 20:00:50 by vcombey           #+#    #+#             */
/*   Updated: 2016/12/30 20:00:53 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft/libft.h"
#include <stdio.h>

void	display_map(void)
{
	int	y;
	int	x;

	y = 0;
	while (y < env()->map_height)
	{
		x = 0;
		while (x < env()->map_width)
		{
			printf("%d ", env()->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
