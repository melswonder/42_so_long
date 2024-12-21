/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_new_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:15:11 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/22 03:03:09 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_setting *setting_new(void)
{
	t_setting *sg;

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
void setting_print(t_setting *sg)
{
	if(sg == NULL)
		return ;
    printf("Window: %p\n", sg->mlx_win);
    printf("Background Image: %p (x:%d, y:%d)\n", sg->buck_img->img, sg->buck_img->x, sg->buck_img->y);
    printf("Character Image: %p (x:%d, y:%d)\n", sg->chara_img->img, sg->chara_img->x, sg->chara_img->y);
}
void setting_delete(t_setting *sg) // free する際にnullチェックをすることで多樹freeを防ぐ
{
	if (sg == NULL)
		return;
	if (sg->buck_img != NULL)
	{
		if (sg->buck_img->img != NULL)
			mlx_destroy_image(sg->mlx,sg->buck_img->img);
	}
	if (sg->buck_img != NULL)
	{
		if (sg->buck_img->img != NULL)
			mlx_destroy_image(sg->mlx,sg->chara_img->img);
	}
	if (sg->mlx_win != NULL)
		mlx_destroy_window(sg->mlx,sg->mlx_win);
	if (sg->mlx != NULL)
	{
		mlx_destroy_display(sg->mlx);
		free(sg->mlx);
	}
	free(sg);
}
