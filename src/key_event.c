/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 12:31:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/18 10:57:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include <stdio.h>
#include "libft.h"

static void	ft_turn(void)
{
	double old_dirx;
	double old_planex;

	if (key()->left)
	{
		old_dirx = cam()->dir.x;
		cam()->dir.x = cam()->dir.x * cos(0.1) - cam()->dir.y * sin(0.1);
		cam()->dir.y = old_dirx * sin(0.1) + cam()->dir.y * cos(0.1);
		old_planex = cam()->plane.x;
		cam()->plane.x = cam()->plane.x * cos(0.1) - cam()->plane.y * sin(0.1);
		cam()->plane.y = old_planex * sin(0.1) + cam()->plane.y * cos(0.1);
	}
	if (key()->right)
	{
		old_dirx = cam()->dir.x;
		cam()->dir.x = cam()->dir.x * cos(-0.1) - cam()->dir.y * sin(-0.1);
		cam()->dir.y = old_dirx * sin(-0.1) + cam()->dir.y * cos(-0.1);
		old_planex = cam()->plane.x;
		cam()->plane.x = cam()->plane.x * cos(-0.1)
			- cam()->plane.y * sin(-0.1);
		cam()->plane.y = old_planex * sin(-0.1) + cam()->plane.y * cos(-0.1);
	}
}

void	erase_img()
{
	ft_memset(env()->ptr, 0, (SCREEN_WIDTH * (SCREEN_HEIGHT)) * 4);
}

int		ft_move(void *param)
{
	(void)param;
	if (key()->up)
	{
		if (env()->map[(int)(cam()->pos.x)][(int)(cam()->pos.y + cam()->dir.y * 0.2)] == 3)
		{
			cam()->pos.x = (double)env()->blue.x;
			cam()->pos.y = (double)env()->blue.y - 0.5;
		}
		else if (env()->map[(int)(cam()->pos.x)][(int)(cam()->pos.y + cam()->dir.y * 0.2)] == 4)
		{
			cam()->pos.x = (double)env()->red.x;
			cam()->pos.y = (double)env()->red.y + 0.5;
		}
		if (env()->map[(int)(cam()->pos.x + cam()->dir.x * 0.2)]
				[(int)cam()->pos.y] == 0)
			cam()->pos.x += cam()->dir.x * 0.2;
		if (env()->map[(int)cam()->pos.x]
				[(int)(cam()->pos.y + cam()->dir.y * 0.2)] == 0)
			cam()->pos.y += cam()->dir.y * 0.2;
	}
	if (key()->down)
	{
		if (env()->map[(int)(cam()->pos.x - cam()->dir.x * 0.2)]
				[(int)cam()->pos.y] == 0)
			cam()->pos.x -= cam()->dir.x * 0.2;
		if (env()->map[(int)cam()->pos.x]
				[(int)(cam()->pos.y - cam()->dir.y * 0.2)] == 0)
			cam()->pos.y -= cam()->dir.y * 0.2;
	}
	ft_turn();
	erase_img();
	ft_wolf();
	mlx_put_image_to_window(env()->mlx, env()->win, env()->img, 0, 0);
	return (0);
}

t_key	*key(void)
{
	static t_key k;

	return (&k);
}

int		ft_key_pressed(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_UP)
		key()->up = 1;
	if (keycode == KEY_DOWN)
		key()->down = 1;
	if (keycode == KEY_RIGHT)
		key()->right = 1;
	if (keycode == KEY_LEFT)
		key()->left = 1;
	if (keycode == KEY_ESCAPE)
		exit(0);
	printf("%d", keycode);
	return (0);
}


int		ft_key_release(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_UP)
		key()->up = 0;
	if (keycode == KEY_DOWN)
		key()->down = 0;
	if (keycode == KEY_RIGHT)
		key()->right = 0;
	if (keycode == KEY_LEFT)
		key()->left = 0;
	if (keycode == KEY_ESCAPE)
		exit(0);
	if (keycode == KEY_Z)
		portal_gun_shoot();
	return (0);
}
