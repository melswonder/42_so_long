/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/29 23:02:16 by hirwatan         ###   ########.fr       */
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

void	put_map(t_map *m)
{
	int	i;

	i = 0;
	while (m->map[i])
	{
		printf("%d:%s\n", i, m->map[i]);
		i++;
	}
}

void	put_all_xpm(t_setting *sg)
{
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	map_info_put(sg, sg->m);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,
		sg->chara_img->y * 64, sg->chara_img->x * 64);
}

int	handle_key_event(int keycode, void *param)
{
	t_setting	*sg;
	static int	count_c = 0;

	sg = (t_setting *)param;
	if (keycode == esc_key)
	{
		setting_delete(sg);
		exit(0);
	}
	if (keycode == a_key || keycode == left_key)
	{
		if (sg->m->map[sg->chara_img->x][sg->chara_img->y - 1] != '1')
			sg->chara_img->y--;
	}
	else if (keycode == d_key || keycode == right_key)
	{
		if (sg->m->map[sg->chara_img->x][sg->chara_img->y + 1] != '1')
			sg->chara_img->y++;
	}
	else if (keycode == w_key || keycode == up_key)
	{
		if (sg->m->map[sg->chara_img->x - 1][sg->chara_img->y] != '1')
			sg->chara_img->x--;
	}
	else if (keycode == s_key || keycode == down_key)
	{
		if (sg->m->map[sg->chara_img->x + 1][sg->chara_img->y] != '1')
			sg->chara_img->x++;
	}
	if (sg->m->map[sg->chara_img->x][sg->chara_img->y] == 'C')
	{
		sg->m->map[sg->chara_img->x][sg->chara_img->y] = '0';
		count_c++;
	}
	if (sg->m->totalC == count_c
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

int	main(void)
{
	t_setting	*sg;
	t_host_info	*host;
	int			ret;

	sg = setting_new();
	ret = check_valid_map(sg->m);
	if (ret == 0)
		return (0);
	host = host_new();
	setup_map_environment(sg, sg->m);
	put_map(sg->m);
	// mlx_hook(sg->mlx_win, 2, 1L << 17, exit_event, sg);
	mlx_hook(sg->mlx_win, 2, 1L << 0, handle_key_event, sg);
	put_all_xpm(sg);
	mlx_loop(sg->mlx);
	return (0);
}
// cc main.c so_long_util.c so_long_new_delete.c -L. -lmlx_Linux -lXext -lX11
// cc main.c so_long_util.c so_long_new_delete.c 
//minilibx-linux/libmlx.a-L.-lXext-lX11