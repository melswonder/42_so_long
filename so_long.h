#ifndef SO_LONG_H
# define SO_LONG_H
#endif

#define x_max 1800
#define y_max 1800

#define w_key 25
#define a_key 38
#define s_key 39
#define d_key 40
#define left_key 65361
#define up_key 65362
#define right_key 65363
#define down_key 65364
#define esc_key 65307

int				handle_key_event(int keycode, void *param);

typedef struct i_data
{
	void		*img;
	int			x;
	int			y;
}				img_data;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*win_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	img_data	*buck_img;
	img_data	*xpm_img;
}				t_setting;

// typedef struct coordinate
// {
// 	int x;
// 	int y;
// } XYcoordinate;