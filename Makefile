NAME = so_long
CC = cc
RM = rm -rf
MLX_DIR = ./minilibx
PRINTF_DIR = ./library/ft_printf
LIBFT_DIR = ./library/libft
GNL_DIR = ./library/get_next_line

CFLAGS = -Wall -Wextra -Werror -I$(GNL_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS = main.c \
       ./utils/free.c \
       ./utils/utils_one.c \
       ./utils/utils_two.c \
       ./utils/utils_three.c \
       $(GNL_DIR)/get_next_line.c \
       $(GNL_DIR)/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a $(MLX_FLAGS) -o $(NAME)

clean:
	${RM} ${OBJS}
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
