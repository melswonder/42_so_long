/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_window_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:56:36 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/30 15:12:20 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_map_environment(t_setting *sg, t_map *m)
{
	sg->chara_img->y = m->start_x;
	sg->chara_img->x = m->start_y;
	printf("human=x:%dy:%d\n", m->start_x, m->start_y);
}

void	map_info_put(t_setting *sg, t_map *m)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (m->map[y])
	{
		x = 0;
		while (m->map[y][x])
		{
			if (m->map[y][x] == '1')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->wall_img->img,
					x * 64, y * 64);
			if (m->map[y][x] == 'C')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->coin_img->img,
					x * 64, y * 64);
			if (m->map[y][x] == 'E')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->exit_img->img,
					x * 64, y * 64);
			x++;
		}
		y++;
	}
	return ;
}
