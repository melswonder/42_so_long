#ifndef SO_LONG_H
#define SO_LONG_H
#endif

#define x_max 1800
#define y_max 1800

typedef struct coordinate
{
	int x;
	int y;
} XYcoordinate;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
