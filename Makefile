NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c backtracking.c check_map.c map_utils.c \
       map_error.c map_new_delete.c map_free_clean.c \
       map_open_read.c so_long_new_delete.c view_window_info.c
OBJS = $(SRCS:.c=.o)
MINILIBX = minilibx-linux/libmlx.a -L. -lXext -lX11

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINILIBX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

v: $(NAME)
	valgrind --leak-check=full ./$(NAME)