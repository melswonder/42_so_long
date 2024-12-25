#ifndef SO_LONG_H
# define SO_LONG_H
#endif

#include "minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <fcntl.h> // open
#include <limits.h>
#include <stdint.h>
#include <stdio.h>  // NULL, size_t
#include <stdlib.h> // malloc, free
#include <string.h> // strlen
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h> // write, read, close

#define x_max 1920 //決めないほうがいい
#define y_max 1200 //決めないほうがいい

#define w_key 119
#define a_key 97
#define s_key 115
#define d_key 100
#define left_key 65361
#define up_key 65362
#define right_key 65363
#define down_key 65364
#define esc_key 65307

typedef struct i_data
{
	void		*img;
	int			x;
	int			y;
	int			width;
	int			height;
}				img_data;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	img_data	*buck_img;
	img_data	*chara_img;
}				t_setting;

typedef struct s_map
{
	char **map; // マップ本体(行の配列)
	int height; // 行数
	int width;  // 列数
	int totalC; // マップに存在する'C'の総数
	int			countP;
	int			countE;
	int start_x; // 'P'のx座標
	int start_y; // 'P'のy座標
}				t_map;

typedef struct s_read
{
	char		buf[2];
	char		*line;
	int			ret;
	int			len;
	char		*new_line;
	int			i;
}				t_read;

void map_new(t_map *m);
char *ft_readline(int fd);
int ft_strlen(const char *str);
int check_errors_findP(t_map *m);
void put_error_map_delete(t_map *m);
int backtrack(t_map *m, int x, int y, int *collected, int **visited);
