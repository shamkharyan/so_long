NAME = so_long

FT_PRINTF_DIR = ft_printf/
FT_PRINTF_NAME = libftprintf.a
FT_PRINTF = $(FT_PRINTF_DIR)$(FT_PRINTF_NAME)

SRCS_DIR = ./srcs/

INCLUDES_DIR = ./includes/

SRCS = \
		$(SRCS_DIR)get_next_line.c \
		$(SRCS_DIR)get_next_line_utils.c \
		$(SRCS_DIR)so_long.c \
		$(SRCS_DIR)game_utils.c \
		$(SRCS_DIR)check_map.c \
		$(SRCS_DIR)so_long_utils.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -Imlx
MLXFLAGS = -Lmlx -lmlx -framework OpenGl -framework Appkit -lm

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(MLXFLAGS) $(OBJS) -o $(NAME) $(FT_PRINTF)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	make -C $(FT_PRINTF_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
