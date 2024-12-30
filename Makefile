NAME = so_long
LIBNAME = so_long.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c backtracking.c check_map.c map_utils.c \
       map_error.c map_new_delete.c map_free_clean.c \
       map_open_read.c so_long_new_delete.c view_window_info.c
OBJS = $(SRCS:.c=.o)
MINILIBX = minilibx-linux/libmlx.a -L. -lXext -lX11

all: $(NAME) $(LIBNAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINILIBX)
	chmod 777 $(NAME)

$(LIBNAME): $(OBJS)
	ar rcs $(LIBNAME) $(OBJS)
	chmod 777 $(LIBNAME)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBNAME)

re: fclean all

v: $(NAME)
	valgrind --leak-check=full ./$(NAME)