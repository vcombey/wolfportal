/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 19:59:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/04 17:07:16 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_camera	*cam(void)
{
	static t_camera	c;

	return (&c);
}

void		init_cam(void)
{
	cam()->height = WALL_HEIGHT / 2;
	cam()->dir.x = -1;
	cam()->dir.y = 0;
	cam()->plane.x = 0;
	cam()->plane.y = 0.66;
}
