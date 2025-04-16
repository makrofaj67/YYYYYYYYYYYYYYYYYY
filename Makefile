BUILD_DIR = ./build
NAME = $(BUILD_DIR)/so_long
NAME_BONUS = $(BUILD_DIR)/so_long_bonus

LIB_DIR = ./lib
SRCS_DIR = ./mandatory/src
INCLUDES_DIR = ./mandatory/include
BONUS_SRCS_DIR = ./mandatory/bonus/src
BONUS_INCLUDES_DIR = ./mandatory/bonus/include

NAME_LIBPRINTFT = $(LIB_DIR)/ft_printf/libftprintf.a
NAME_GETNEXTLINE = $(LIB_DIR)/get_next_line/getnextline.a
NAME_MINILIBX = $(LIB_DIR)/minilibx-linux/libmlx_Linux.a
STATIC_LIBS = $(NAME_LIBPRINTFT) $(NAME_GETNEXTLINE) $(NAME_MINILIBX)

CC = gcc
CFLAGS = 
MLX_FLAGS = -I$(LIB_DIR)/minilibx-linux -L$(LIB_DIR)/minilibx-linux -lmlx -lX11 -lXext -lm

SRCS = $(shell find $(SRCS_DIR) -type f -name '*.c')
BONUS_SRCS = $(shell find $(BONUS_SRCS_DIR) -type f -name '*.c' 2>/dev/null)
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)
bonus: $(NAME_BONUS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(NAME_GETNEXTLINE):
	@$(MAKE) -sC $(LIB_DIR)/get_next_line all

$(NAME_LIBPRINTFT):
	@$(MAKE) -sC $(LIB_DIR)/ft_printf all

$(NAME_MINILIBX):
	@$(MAKE) -sC $(LIB_DIR)/minilibx-linux all

$(NAME): $(OBJS) $(STATIC_LIBS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIBS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) derlendi."

$(NAME_BONUS): $(BONUS_OBJS) $(STATIC_LIBS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(STATIC_LIBS) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) derlendi."


$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(BONUS_INCLUDES_DIR) -I$(LIB_DIR)/minilibx-linux -c $< -o $@
$(BUILD_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(BONUS_INCLUDES_DIR) -I$(LIB_DIR)/minilibx-linux -c $< -o $@


clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -sC $(LIB_DIR)/ft_printf clean
	@$(MAKE) -sC $(LIB_DIR)/get_next_line clean
	@$(MAKE) -sC $(LIB_DIR)/minilibx-linux clean
	@echo "Obje dosyaları ve kütüphane nesne dosyaları temizlendi."

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -f $(NAME_MINILIBX)
	@$(MAKE) -sC $(LIB_DIR)/ft_printf fclean
	@$(MAKE) -sC $(LIB_DIR)/get_next_line fclean
	@rm -rf $(BUILD_DIR)
	@echo "Programlar, obje dosyaları, kütüphaneler ve build dizini temizlendi."

re: fclean all

dev: all clean
	@$(NAME)

.PHONY: all bonus clean fclean re start
