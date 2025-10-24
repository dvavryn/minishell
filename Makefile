# Makefile for Minishell Project

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I./libs/libft

# Suppress directory change
MAKEFLAGS += --no-print-directory

# Project name
NAME = minishell

# Directories
SRC_DIR = ./src
OBJ_DIR = ./objs
LIBFT_DIR = ./libs/libft

# Source files
SRC := \
        src/builtin/bi_cd.c \
        src/builtin/bi_echo.c \
        src/builtin/bi_env.c \
        src/builtin/bi_exit.c \
        src/builtin/bi_export_utils.c \
        src/builtin/bi_export.c \
        src/builtin/bi_pwd.c \
        src/builtin/bi_unset.c \
        \
        src/executer/executer.c \
        src/executer/get_path.c \
        src/executer/open_files.c \
        src/executer/pipeline.c \
        src/executer/utils.c \
        \
        src/expander/expand_tokens.c \
        src/expander/expand_word.c \
        src/expander/expander.c \
        src/expander/split_expanded_var.c \
        \
        src/free/free_all.c \
        src/free/free_cmd.c \
        src/free/free_split.c \
        src/free/free_tokens`.c \
        \
        src/parser/heredoc/clean_hd.c \
        src/parser/heredoc/expand_heredoc.c \
        src/parser/heredoc/get_heredoc_input.c \
        src/parser/heredoc/get_heredoc_name.c \
        src/parser/heredoc/heredoc.c \
        src/parser/add_cmd.c \
        src/parser/cleanup_args.c \
        src/parser/cmd_split_join.c \
        src/parser/get_cmd.c \
        src/parser/isclosed.c \
        src/parser/parser.c \
        \
        src/tokenizer/add_token.c \
        src/tokenizer/tokenizer.c \
        \
        src/utils/ft_strcmp.c \
        src/utils/ft_strjoin_endl.c \
        src/utils/ft_strndup.c \
        src/utils/ms_getenv.c \
        src/utils/ms_lstlast.c \
        src/utils/ms_perror.c \
        src/utils/split_copy.c \
        \
        src/ft_exit.c \
        src/main.c \
        src/prompt.c \
        src/signals.c \
        src/startup.c

OBJS := $(patsubst src/%, $(OBJ_DIR)/%, $(SRC:.c=.o))
HEAD := $(wildcard inc/*.h)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Rules
all: $(OBJ_DIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: src/%.c $(HEAD)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

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

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug