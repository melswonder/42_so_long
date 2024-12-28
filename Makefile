NAME = so_long
LIB = so_long.a

SRCS = check_map.c map_new_delete.c map_open_read.c map_utils.c so_long_util.c so_long_new_delete.c backtracking.c main.c
OBJS = $(SRCS:.c=.o)
MINI = minilibx-linux/libmlx.a -L. -lXext -lX11
CC = cc
# CC = cc42
CFLAGS = -Wall -Wextra -Werror -I .

VAL = valgrind --leak-check=full ./$(NAME)

$(LIB): $(OBJS)
	ar rc $(LIB) $(OBJS)
	ranlib $(LIB)
	chmod 755 $(LIB)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINI)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

v: $(NAME)
	$(VAL)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re