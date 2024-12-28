/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_window_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:56:36 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/28 18:34:47 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setup_map_environment(t_setting *sg,t_map *m)
{
	sg->chara_img->x = sg->chara_img->height * (m->start_x + 1);
	sg->chara_img->y = sg->chara_img->width * (m->start_y + 1);
	printf("x:%d,y:%d",m->start_x,m->start_y);
}