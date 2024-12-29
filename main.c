/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/29 13:35:20 by hirwatan         ###   ########.fr       */
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

// void put_all_xpm(t_setting *sg,t_map *m) mapも再描画すう
void put_all_xpm(t_setting *sg)
{
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,
		sg->chara_img->x, sg->chara_img->y);
	map_info_put(sg,sg->m);
}

// int	handle_key_event(int keycode, void *param, t_map *m)　再描画のときにmap情報が必要
int	handle_key_event(int keycode, void *param)
{
	t_setting	*sg;

	
	sg = (t_setting *)param;
	if (keycode == esc_key)
	{
		setting_delete(sg);
		exit(0);
	}
	printf("x:%d y:%d\n", sg->chara_img->x, sg->chara_img->y); //座標出力
	if (keycode == w_key || (keycode == up_key && sg->chara_img->y > 0))
		sg->chara_img->y -= 64;
	if (keycode == s_key || (keycode == down_key && sg->chara_img->y < y_max))
		sg->chara_img->y += 64;
	if (keycode == a_key || (keycode == left_key && sg->chara_img->x > 0))
		sg->chara_img->x -= 64;
	if (keycode == d_key || (keycode == right_key && sg->chara_img->x < x_max))
		sg->chara_img->x += 64;
	mlx_clear_window(sg->mlx, sg->mlx_win); //再描画
	put_all_xpm(sg);
	// mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	// mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,
	// 	sg->chara_img->x, sg->chara_img->y);
	return (0);
}
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
	setup_map_environment(sg,sg->m);
	mlx_hook(sg->mlx_win, 2, 1L << 0, handle_key_event, sg);
	put_all_xpm(sg);
	mlx_loop(sg->mlx);
	return (0);
}
// cc main.c so_long_util.c so_long_new_delete.c -L. -lmlx_Linux -lXext -lX11
// cc main.c so_long_util.c so_long_new_delete.c minilibx-linux/libmlx.a -L.-lXext -lX11