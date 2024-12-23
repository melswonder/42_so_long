#ifndef SO_LONG_H
# define SO_LONG_H
#endif

#include "minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define x_max 1920
#define y_max 1200

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


int				handle_key_event(int keycode, void *param);
void			*ft_calloc(size_t count, size_t size);
int				close_window(t_setting *sg);
void			setting_delete(t_setting *sg);
void	setting_print(t_setting *sg);
t_setting		*setting_new(void);