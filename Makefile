# Makefile for Minishell Project

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -g
DEBUG_FLAGS = -g
INCLUDES = -I./inc -I./libs/libft

# Project name
NAME = minishell

# Directories
SRC_DIR = ./src
OBJ_DIR = ./objs
LIBFT_DIR = ./libs/libft

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

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
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -lreadline

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