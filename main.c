/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/18 22:35:18 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	setting_delete(void)
{
}
void	setting_print(void)
{
}

void	img_delete(void)
{
}
void	img_print(void)
{
}

int	close_window(void *param)
{
	t_setting	*sg;

	sg = (t_setting *)param;
	mlx_destroy_image(sg->mlx, sg->buck_img->img);
	mlx_destroy_image(sg->mlx, sg->chara_img->img);
	mlx_destroy_window(sg->mlx, sg->mlx_win);
	mlx_destroy_display(sg->mlx);
	return (0);
}
t_setting	*setting_new(void)
{
	t_setting	*sg;

	sg = ft_calloc(1, sizeof(t_setting));
	sg->mlx = mlx_init();
	sg->mlx_win = mlx_new_window(sg->mlx, 1920, 1200, "HELLO WOULD!");
	// sg->addr = mlx_get_data_addr(sg->board_img, &sg->bits_per_pixel,
	// 		&sg->line_length, &sg->endian); why?
	// sg->board_img = mlx_new_image(sg->mlx, 1920, 1200);
	// imgs
	sg->buck_img = malloc(sizeof(img_data));
	sg->buck_img->img = mlx_xpm_file_to_image(sg->mlx, "xpm/buckground.xpm",
			&sg->buck_img->x, &sg->buck_img->y);
	sg->chara_img = malloc(sizeof(img_data));
	sg->chara_img->x = 0;
	sg->chara_img->y = 0;
	sg->chara_img->img = mlx_xpm_file_to_image(sg->mlx,
			"xpm/main_character.xpm", &sg->chara_img->width,
			&sg->chara_img->height);
	return (sg);
}

int	main(void)
{
	t_setting	*sg;

	sg = setting_new();
	mlx_hook(sg->mlx_win, 2, 1L << 0, handle_key_event, sg);
	// mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->board_img, 0, 0); nazo
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,sg->chara_img->x, sg->chara_img->y);
	mlx_hook(sg->mlx_win, 17, 0, close_window, sg);
	mlx_loop(sg->mlx);
	return (0);
}
int	handle_key_event(int keycode, void *param)
{
	t_setting	*sg;

	sg = (t_setting *)param;
	if (keycode == esc_key)
	{
		printf("esc\n");
		exit(0);
	}
	printf("x:%d y:%d\n", sg->chara_img->x, sg->chara_img->y);
	// sg->xpm_img->y += (keycode == w_key) * 200 - (keycode == s_key) * 200;
	// sg->xpm_img->x += (keycode == d_key) * 200 - (keycode == a_key) * 200;
	// sg->xpm_img->y += (keycode == up_key) * 200 - (keycode == down_key)
	//* 200;
	// sg->xpm_img->x += (keycode == down_key) * 200 - (keycode == left_key)
	//* 200;
	if (keycode == w_key || keycode == up_key && sg->chara_img->y > 0) 
		sg->chara_img->y -= 200;
	if (keycode == s_key || keycode == down_key && sg->chara_img->y < y_max)
		sg->chara_img->y += 200;
	if (keycode == a_key || keycode == left_key && sg->chara_img->x > 0)
		sg->chara_img->x -= 200;
	if (keycode == d_key || keycode == right_key && sg->chara_img->x < x_max)
		sg->chara_img->x += 200;
	mlx_clear_window(sg->mlx, sg->mlx_win); //再描画
	// mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->board_img, 0, 0);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->buck_img->img, 0, 0);
	mlx_put_image_to_window(sg->mlx, sg->mlx_win, sg->chara_img->img,
		sg->chara_img->x, sg->chara_img->y);
	return (0);
}
// cc main.c -L. -lmlx_Linux -lXext -lX11
// cc main.c minilibx-linux/libmlx.a -L. -lXext -lX11