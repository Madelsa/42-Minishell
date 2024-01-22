#/!bin/bash

valgrind --suppressions=/home/vscode/src/readline.supp --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell