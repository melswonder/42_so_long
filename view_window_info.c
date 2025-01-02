/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_window_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:56:36 by hirwatan          #+#    #+#             */
/*   Updated: 2025/01/02 18:59:37 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_map_environment(t_setting *sg)
{
	if (!sg || !sg->m)
		return ;
	sg->chara_img->y = sg->m->start_x;
	sg->chara_img->x = sg->m->start_y;
}

void	map_info_put(t_setting *sg)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= sg->m->height - 1)
	{
		x = 0;
		while (x <= sg->m->width - 1)
		{
			if (sg->m->map[y][x] == '1')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->wall_img->img,
					x * 64, y * 64);
			if (sg->m->map[y][x] == 'C')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->coin_img->img,
					x * 64, y * 64);
			if (sg->m->map[y][x] == 'E')
				mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->exit_img->img,
					x * 64, y * 64);
			x++;
		}
		y++;
	}
}
//map探索のときにPの地点を0に置き換えればいい。
// while (sg->m->map[y])
// {
// x = 0;
// while (sg->m->map[y][x])