#include "minilibx-linux/mlx.h"
#include "so_long.h"

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	void	*buck_img;
	void	*main_img;
	int		x;
	int		y;
	t_setting	img;

	x = 0;
	y = 0;
	mlx = mlx_init(); // windowを作るためにひつよなもの
	mlx_win = mlx_new_window(mlx, 1920, 1080, "HEllo would!");
	if (!mlx_win)
		return (0);
	img.img = mlx_new_image(mlx, 1920, 1080); // 1項目目
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian); // 2項目目
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);  //ズレを修正
	buck_img = mlx_xpm_file_to_image(mlx, "xpm/buckground.xpm", &x, &y);
	main_img = mlx_xpm_file_to_image(mlx, "xpm/main_character.xpm", &x, &y);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);  //ここの引数でどこに置くのかが変わる
	mlx_put_image_to_window(mlx, mlx_win, buck_img, 0, 0); //ここの引数でどこに置くのかが変わる
	mlx_put_image_to_window(mlx, mlx_win, main_img, 0, 0); //ここの引数でどこに置くのかが変わる
	mlx_loop(mlx);                                        
		//これがないとすぐにwindowが閉じてしまう
}

// cc main.c -L. -lmlx_Linux -lXext -lX11
// cc main.c minilibx-linux/libmlx.a -L. -lXext -lX11
