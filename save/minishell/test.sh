make all -C libft
make all clean
clear

./minishell
# valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.supp ./minishell