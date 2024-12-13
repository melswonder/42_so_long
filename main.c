/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/13 14:41:51 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// typedef struct s_vars
// {
// 	void *mlx;
// 	void *win;
// }	t_vars;

// int close(int keycode,t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx,vars->win);
// 	return(0);
// }
// int main(void)
// {
// 	t_vars	vars;

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
// 	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
// 	mlx_loop(vars.mlx);
// }

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}			t_data;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int x;
	int y;
	x = 0;
	y = 0;
	int xx = 200;
	int yy = 200;
	t_data	img;

	void *buck_img;
	void *xpm_img;
	mlx = mlx_init(); //最初に宣言する
	mlx_win = mlx_new_window(mlx, 1920, 1200, "HELLO WOULD!");
	img.img = mlx_new_image(mlx, 1920, 1200);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	buck_img = mlx_xpm_file_to_image(mlx, "xpm/buckground.xpm", &x, &y);
	xpm_img = mlx_xpm_file_to_image(mlx, "xpm/main_character.xpm", &xx, &yy);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, buck_img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, xpm_img, 200, 200);
	mlx_loop(mlx);
}
// cc main.c -L. -lmlx_Linux -lXext -lX11
// cc main.c minilibx-linux/libmlx.a -L. -lXext -lX11