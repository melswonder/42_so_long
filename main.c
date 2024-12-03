/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:28:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/12/03 21:27:23 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// int main(void)
// {
// 	void *mlx;
// 	t_data img;

// 	mlx = mlx_init();		//最初に宣言する
// 	img.img = mlx_new_image(mlx,1200,1200); //imgを置く
// 	img.addr = mlx_get_data_addr(
// 		img.img,
// 		&img.bits_per_pixel,
// 		&img.line_length,
// 		&img.endian
// 	);
// 	// mlx_win = mlx_new_window(mlx,1200,1200,"Hello");
// 	// mlx_loop(mlx);

// }

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	int		x;
// 	int		y;
// 	t_data	img;

// 	x = 100;
// 	y = 100;
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "HELLO WOULD!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	mlx_xpm_file_to_image(mlx, "xpm/1.xpm", &x, &y);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	t_data	img;

	void *xpm_img; // XPM画像用の新しいポインタを追加
	x = 100;
	y = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 2000, 2000, "HELLO WOULD!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	// XPM画像を読み込む
	xpm_img = mlx_xpm_file_to_image(mlx, "xpm/1.xpm", &x, &y);
	// 画像が正常に読み込まれたかチェック
	if (xpm_img == NULL)
	{
		printf("XPM画像の読み込みに失敗しました\n");
		return (1);
	}
	// 背景画像を描画
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// XPM画像を描画 (位置を指定)
	mlx_put_image_to_window(mlx, mlx_win, xpm_img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
// cc main.c -L. -lmlx_Linux -lXext -lX11