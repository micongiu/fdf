NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -g -I./include -O2

SRCS = ./src/main.c ./src/read_and_store.c ./gnl/get_next_line_utils.c ./gnl/get_next_line.c ./src/utility.c ./src/utility_2.c  \
		./src/ft_mlx.c ./src/print_map.c ./src/colour_management.c
SRC_DIRS = ./src
OBJS = ${SRCS:.c=.o}

MLX_LIBS	+= -L./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd
PRINTF		:= ft_printf/libftprintf.a
LIBFT		:= libft/libft.a

GREEN		=\033[0;32m
RED			=\033[0;31m
BLUE		=\033[0;34m
COLOUR_END	=\033[0m

OBJ_DIR = ./obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,${SRCS})

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p ./obj/ft_printf
	@mkdir -p ./obj/libft
	@mkdir -p ./obj/ft_printf
	@$(CC) -g -c $< -o $@;

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ./minilibx-linux/
	@$(MAKE) -C ft_printf/
	@$(MAKE) -C ./libft/
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIBS) $(PRINTF) $(LIBFT) -o $(NAME)
	@echo "$(RED)EVERYTHING COMPILE!$(COLOUR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -sC ft_printf/
	@make clean -C minilibx-linux/
	@make clean -sC libft/
	@rm -rf $(OBJS)
	@${RM} -r ${OBJ_DIR}
	@echo "$(GREEN)EVERYTHING HAS CLEAN!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@$(RM) -f $(PRINTF)
	@$(RM) -f $(LIBFT)
	@$(RM) -f $(minilibx-linux/)libmlx.a
	@echo "$(BLUE)EVERYTHING HAS FCLEAN!$(COLOUR_END)"

re: fclean all
	@$(MAKE)

.PHONY: all clean fclean re