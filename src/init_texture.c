/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 21:49:16 by vcombey           #+#    #+#             */
/*   Updated: 2017/04/27 14:46:49 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>
#include <mlx.h>

int			init_wall_texture(void)
{
	if (!(texture()->img = mlx_xpm_file_to_image(env()->mlx,
					"img/mur_portal.xpm",
	&texture()->width, &texture()->height)))
		return (ft_retmsg("cannot load image ol.xpm :/", 2));
	texture()->ptr = mlx_get_data_addr(texture()->img, &texture()->bpp,
	&texture()->size_line, &texture()->endian);
	return (0);
}

int			init_portal_gun_texture(void)
{
	if (!(gun()->img = mlx_xpm_file_to_image(env()->mlx,
					"img/portal_gun.xpm",
	&gun()->width, &gun()->height)))
		return (ft_retmsg("cannot load image portal_gun.xpm :/", 2));
	gun()->ptr = mlx_get_data_addr(gun()->img, &gun()->bpp,
	&gun()->size_line, &gun()->endian);
	return (0);
}

int			init_portal_blue_texture(void)
{
	if (!(portal_blue()->img = mlx_xpm_file_to_image(env()->mlx,
					"img/portal_bleu.xpm",
	&portal_blue()->width, &portal_blue()->height)))
		return (ft_retmsg("cannot load image portal_bleu.xpm :/", 2));
	portal_blue()->ptr = mlx_get_data_addr(portal_blue()->img,
			&portal_blue()->bpp,
	&portal_blue()->size_line, &portal_blue()->endian);
	return (0);
}

int			init_portal_red_texture(void)
{
	if (!(portal_red()->img = mlx_xpm_file_to_image(env()->mlx,
					"img/portal_orange.xpm",
	&portal_red()->width, &portal_red()->height)))
		return (ft_retmsg("cannot load image portal_orange.xpm :/", 2));
	portal_red()->ptr = mlx_get_data_addr(portal_red()->img, &portal_red()->bpp,
	&portal_red()->size_line, &portal_red()->endian);
	return (0);
}

int			init_tourelle_texture(void)
{
	if (!(tourelle()->img = mlx_xpm_file_to_image(env()->mlx,
					"img/tourelle.xpm",
	&tourelle()->width, &tourelle()->height)))
		return (ft_retmsg("cannot load image tourelle.xpm :/", 2));
	tourelle()->ptr = mlx_get_data_addr(tourelle()->img, &tourelle()->bpp,
	&tourelle()->size_line, &tourelle()->endian);
	return (0);
}
