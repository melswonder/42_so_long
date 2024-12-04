/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/04 15:48:26 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct s_vars
{
	void *mlx;
	void *win;
}	t_vars;

int close(int keycode,t_vars *vars)
{
	mlx_destroy_window(vars->mlx,vars->win);
	return(0);
}
int main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}

// typedef struct s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_data;

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	int		x;
// 	int		y;
// 	t_data	img;

// 	void *xpm_img;
// 	x = 100;
// 	y = 100;
// 	mlx = mlx_init(); //最初に宣言する
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "HELLO WOULD!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	xpm_img = mlx_xpm_file_to_image(mlx, "xpm/1.xpm", &x, &y);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_put_image_to_window(mlx, mlx_win, xpm_img, 0, 0);
// 	mlx_loop(mlx);
// }
// cc main.c -L. -lmlx_Linux -lXext -lX11