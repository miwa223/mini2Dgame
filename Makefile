NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
SRCS = src/main.c src/init_struct.c src/set_map_info.c src/press_key.c src/put_sprites.c \
		src/validation.c src/exit.c src/get_next_line.c
OBJS = $(SRCS:%.c=%.o)
DEPENDS = $(OBJS:%.o=%.d)
LIBFT_DIR = libft/
LIBFT_LIB = libft.a
MINILIBX_DIR = mlx/
# MINILIBX_LIB = libmlx_Linux.a
MINILIBX_LIB = libmlx_Darwin.a

all: $(NAME)

# $(NAME): $(OBJS)
# 	make -C $(MINILIBX_DIR)
# 	make -C $(LIBFT_DIR)
# 	$(CC) $(CFLAGS) $(OBJS) -L. $(LIBFT_DIR)$(LIBFT_LIB) -L. $(MINILIBX_DIR)$(MINILIBX_LIB) -Imlx -lXext -lX11 -o $@
$(NAME): $(OBJS)
	make -C $(MINILIBX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(OBJS) -L. $(LIBFT_DIR)$(LIBFT_LIB) -L. $(MINILIBX_DIR)$(MINILIBX_LIB) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# .c.o:
# 	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean:
	make clean -C $(MINILIBX_DIR)
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(DEPENDS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

bonus: all

re: fclean all

-include $(DEPENDS)
.PHONY: all clean fclean re bonus
