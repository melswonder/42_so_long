/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2025/01/02 19:46:36 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void esc_free(t_setting *sg)
// {
// 		printf("esc\n");
// 		setting_delete(sg);
// 		free(sg);
// 		exit(0);
// }

void	put_all_xpm(t_setting *sg)
{
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	map_info_put(sg);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,
		sg->chara_img->y * 64, sg->chara_img->x * 64);
}

void map_move(int keycode,t_setting *sg)
{
	if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		if (sg->m->map[sg->chara_img->x][sg->chara_img->y - 1] != '1')
			sg->chara_img->y--;
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		if (sg->m->map[sg->chara_img->x][sg->chara_img->y + 1] != '1')
			sg->chara_img->y++;
	}
	else if (keycode == W_KEY || keycode == UP_KEY)
	{
		if (sg->m->map[sg->chara_img->x - 1][sg->chara_img->y] != '1')
			sg->chara_img->x--;
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		if (sg->m->map[sg->chara_img->x + 1][sg->chara_img->y] != '1')
			sg->chara_img->x++;
	}	
}


int	handle_key_event(int keycode, void *param)
{
	t_setting	*sg;
	static int	count_c = 0;

	sg = (t_setting *)param;
	if (keycode == ESC_KEY)
	{
		setting_delete(sg);
		exit(0);
	}
	map_move(keycode,sg);
	if (sg->m->map[sg->chara_img->x][sg->chara_img->y] == 'C')
	{
		sg->m->map[sg->chara_img->x][sg->chara_img->y] = '0';
		count_c++;
	}
	if (sg->m->total_c == count_c
		&& sg->m->map[sg->chara_img->x][sg->chara_img->y] == 'E')
	{
		setting_delete(sg);
		exit(0);
	}
	mlx_clear_window(sg->mlx, sg->mlx_win);
	put_all_xpm(sg);
	return (0);
}

// int exit_event(void*param)
// {
// 	t_setting *sg;
// 	sg = (t_setting *)param;
// 	setting_delete(sg);
// 	exit(0);
// }

// void setting_put(t_setting *sg)
// {
	
// 	printf("");
// }

int	main(void)
{
	t_setting	*sg;
	// t_host_info	*host;
	int			ret;

	sg = (t_setting *)malloc(sizeof(t_setting));
	if(!sg)
		return (1);
	sg->m = NULL;
	sg->mlx = NULL;
	sg->mlx_win = NULL;
	sg->m = (t_map*)malloc(sizeof(t_map));
	if(!sg->m)
		return (free(sg),1);
	ret = check_valid_map(sg->m);
	if (ret == 0)
		return (free(sg->m),free(sg),0);
	sg = setting_new(sg);
	setup_map_environment(sg);
	// host = host_new();
	mlx_hook(sg->mlx_win, 2, 1L << 0, handle_key_event, sg);
	put_all_xpm(sg);
	mlx_loop(sg->mlx);
	setting_delete(sg);
	// free(host); 歩数カウントまた後で
	return (0);
}
// cc main.c so_long_util.c so_long_new_delete.c -L. -lmlx_Linux -lXext -lX11
// cc main.c so_long_util.c so_long_new_delete.c 
//minilibx-linux/libmlx.a-L.-lXext-lX11