/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 12:27:53 by rbadia            #+#    #+#             */
/*   Updated: 2017/04/25 17:22:06 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>
#include <mlx.h>

t_env		*env(void)
{
	static t_env	e;

	return (&e);
}

t_texture	*texture(void)
{
	static t_texture	t;

	return (&t);
}

t_texture	*gun(void)
{
	static t_texture	g;

	return (&g);
}

t_texture	*portal_blue(void)
{
	static t_texture	p;

	return (&p);
}

t_texture	*portal_red(void)
{
	static t_texture	p;

	return (&p);
}

int			init_wall_texture(void)
{
	if (!(texture()->img = mlx_xpm_file_to_image(env()->mlx, "mur_portal.xpm",
	&texture()->width, &texture()->height)))
		return (ft_retmsg("cannot load image ol.xpm :/", 2));
	texture()->ptr = mlx_get_data_addr(texture()->img, &texture()->bpp,
	&texture()->size_line, &texture()->endian);
	return (0);
}

int			init_portal_gun_texture(void)
{
	if (!(gun()->img = mlx_xpm_file_to_image(env()->mlx, "portal_gun.xpm",
	&gun()->width, &gun()->height)))
		return (ft_retmsg("cannot load image portal_gun.xpm :/", 2));
	gun()->ptr = mlx_get_data_addr(gun()->img, &gun()->bpp,
	&gun()->size_line, &gun()->endian);
	return (0);
}

int			init_portal_blue_texture(void)
{
	if (!(portal_blue()->img = mlx_xpm_file_to_image(env()->mlx, "portal_bleu.xpm",
	&portal_blue()->width, &portal_blue()->height)))
		return (ft_retmsg("cannot load image portal_bleu.xpm :/", 2));
	portal_blue()->ptr = mlx_get_data_addr(portal_blue()->img, &portal_blue()->bpp,
	&portal_blue()->size_line, &portal_blue()->endian);
	return (0);
}

int			init_portal_red_texture(void)
{
	if (!(portal_red()->img = mlx_xpm_file_to_image(env()->mlx, "portal_orange.xpm",
	&portal_red()->width, &portal_red()->height)))
		return (ft_retmsg("cannot load image portal_orange.xpm :/", 2));
	portal_red()->ptr = mlx_get_data_addr(portal_red()->img, &portal_red()->bpp,
	&portal_red()->size_line, &portal_red()->endian);
	return (0);
}

int			init_env(char *file)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)file;
	env()->win = NULL;
	env()->img = NULL;
	env()->mlx = NULL;
	ft_parse_input(file);
	if (!env()->mlx && !(env()->mlx = mlx_init()))
		return (ft_retmsg("mlx problem", 2));
	if (!env()->win && !(env()->win = mlx_new_window(env()->mlx, SCREEN_WIDTH,
	SCREEN_HEIGHT, "Wolf3d")))
		return (ft_retmsg("mlx problem", 2));
	if (!env()->img && !(env()->img = mlx_new_image(env()->mlx, SCREEN_WIDTH,
	SCREEN_HEIGHT)))
		return (ft_retmsg("mlx problem", 2));
	env()->ptr = mlx_get_data_addr(env()->img, &env()->bpp, &env()->size_line,
	&env()->endian);
	env()->map[4][6] = 3;
	env()->map[0][4] = 4;
	env()->red.x = 4;
	env()->red.y = 6;
	env()->blue.x = 0;
	env()->blue.y = 4;
	env()->sidered = 2;
	env()->sideblue = -1;
	return (0);
}
