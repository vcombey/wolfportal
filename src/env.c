/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 12:27:53 by rbadia            #+#    #+#             */
/*   Updated: 2017/04/28 21:17:46 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>
#include <mlx.h>

void	init_portal_in_env(void)
{
	env()->map[15][10] = 3;
	env()->map[17][16] = 4;
	env()->red.x = 17;
	env()->red.y = 16;
	env()->blue.x = 15;
	env()->blue.y = 10;
	env()->sidered = 1;
	env()->sideblue = -1;
}

int		init_env(char *file)
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
	env()->life = 100;
	init_portal_in_env();
	return (0);
}
