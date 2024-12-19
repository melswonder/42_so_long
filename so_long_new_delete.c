/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_new_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loremipsum <loremipsum@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:15:11 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/19 12:42:51 by loremipsum       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
void	setting_print(void)
{
    printf("mlx:%d,mlx_win:")
	
}
void	setting_delete(t_setting *sg)
{
	mlx_destroy_image(sg->mlx, sg->buck_img->img);
	mlx_destroy_image(sg->mlx, sg->chara_img->img);
	mlx_destroy_window(sg->mlx, sg->mlx_win);
	mlx_destroy_display(sg->mlx);
	free(sg);
}
