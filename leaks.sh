#/!bin/bash

valgrind --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell