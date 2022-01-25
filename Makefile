NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
SRCS = fractol.c
OBJS = $(SRCS:%.c=%.o)

LIBFT_DIR = libft/
LIBFT_LIB = libft.a
MINILIBX_DIR = mlx/
MINILIBX_LIB = libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJS)
	cd $(MINILIBX_DIR) && ./configure
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L. $(LIBFT_DIR)$(LIBFT_LIB) -L. $(MINILIBX_DIR)$(MINILIBX_LIB) -Imlx -lXext -lX11 -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd $(LIBFT_DIR) && make clean
	cd $(MINILIBX_DIR) && make clean
	rm -f $(OBJS) *.d

fclean: clean
	cd $(LIBFT_DIR) && make fclean
	rm -f $(NAME) $(LIBFT_DIR)$(LIBFT_LIB)

bonus: all

re: fclean all

.PHONY: all clean fclean re bonus
