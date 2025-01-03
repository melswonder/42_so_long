/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_new_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:15:11 by hirwatan          #+#    #+#             */
/*   Updated: 2025/01/02 19:46:03 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_setting	*all_img_coordinate_new(t_setting *sg)
{
	sg->buck_img->img = mlx_xpm_file_to_image(sg->mlx, "xpm/buck.xpm",
			&sg->buck_img->x, &sg->buck_img->y);
	sg->chara_img = malloc(sizeof(t_img_data));
	sg->chara_img->x = 0;
	sg->chara_img->y = 0;
	sg->chara_img->img = mlx_xpm_file_to_image(sg->mlx,
			"xpm/main_character.xpm", &sg->chara_img->width,
			&sg->chara_img->height);
	sg->wall_img = malloc(sizeof(t_img_data));
	sg->wall_img->x = 0;
	sg->wall_img->y = 0;
	sg->wall_img->img = mlx_xpm_file_to_image(sg->mlx, "xpm/wall.xpm",
			&sg->wall_img->width, &sg->wall_img->height);
	sg->coin_img = malloc(sizeof(t_img_data));
	sg->coin_img->x = 0;
	sg->coin_img->y = 0;
	sg->coin_img->img = mlx_xpm_file_to_image(sg->mlx, "xpm/coin.xpm",
			&sg->coin_img->width, &sg->coin_img->height);
	sg->exit_img = malloc(sizeof(t_img_data));
	sg->exit_img->x = 0;
	sg->exit_img->y = 0;
	sg->exit_img->img = mlx_xpm_file_to_image(sg->mlx, "xpm/exit.xpm",
			&sg->exit_img->width, &sg->exit_img->height);
	return (sg);
}

t_host_info	*host_new(void)
{
	t_host_info	*host;

	host = (t_host_info *)malloc(sizeof(t_host_info));
	if(!host)
		return (0);
	host->move_count = 0;
	return (host);
}

t_setting	*setting_new(t_setting *sg)
{
	sg->mlx = mlx_init();
	sg->mlx_win = mlx_new_window(sg->mlx, 1920, 1200, "SO_LONG");
	sg->buck_img = malloc(sizeof(t_img_data));
	sg = all_img_coordinate_new(sg);
	return (sg);
}

int	img_delete(t_setting *sg)
{
	if (!sg)
		return (0);
	mlx_destroy_image(sg->mlx, sg->buck_img->img);
	free(sg->buck_img);
	mlx_destroy_image(sg->mlx, sg->chara_img->img);
	free(sg->chara_img);
	mlx_destroy_image(sg->mlx, sg->wall_img->img);
	free(sg->wall_img);
	mlx_destroy_image(sg->mlx, sg->coin_img->img);
	free(sg->coin_img);
	mlx_destroy_image(sg->mlx, sg->exit_img->img);
	free(sg->exit_img);
	// free(sg);
	return (1);
}

void	setting_delete(t_setting *sg)
{
	int	i;

	if (sg->m && sg->m->map)
	{
		i = 0;
		while (i < sg->m->height)
			free(sg->m->map[i++]);
		free(sg->m->map);
		free(sg->m);
	}
	if (img_delete(sg))
	{
		mlx_destroy_window(sg->mlx, sg->mlx_win);
		mlx_destroy_display(sg->mlx);
		free(sg->mlx);
		free(sg);
	}
}
