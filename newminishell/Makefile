# Makefile for Minishell Project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g 
# -fsanitize=address
DEBUG_FLAGS = -g
INCLUDES = -I./inc -I./libs/libft

# Supress directory change
MAKEFLAGS += --no-print-directory

# Project name
NAME = minishell

# Directories
SRC_DIR = ./src
OBJ_DIR = ./objs
LIBFT_DIR = ./libft

# Source files

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Object files removed$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 $(NAME) and $(LIBFT) removed$(NC)"

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug