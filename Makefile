CC = gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g

NAME = minishell
LIBFT = libft/libft.a

OBJ_DIR = obj/

SRC = tokenization/tokenizer.c\
tokenization/tokenizer_utils.c\
main.c\
init_free/init.c\
init_free/init_utils.c\
signal.c\
input_validation/syntax_checker.c\
input_validation/syntax_checker_utils.c\
builtin/helper.c\
builtin/expansion.c\
builtin/cd.c\
builtin/echo.c\
builtin/env.c\
builtin/exit.c\
builtin/export.c\
builtin/pwd.c\
builtin/unset.c\
init_free/free_me.c\
execution/execution_manager.c\
execution/execution_utils.c\
execution/cmd_execution.c\
execution/cmd_input_processing.c\
execution/handle_heredoc.c\
execution/path_utils.c\
execution/path_utils2.c\
execution/process_management.c\
parsing/parser.c\
parsing/parser_utils.c\

# Generate the object files, each one placed inside obj/ based on its directory structure
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Default target
all: $(NAME)

# Ensure the obj/ directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create the necessary subdirectories under obj/
$(OBJ_DIR)%/:
	@mkdir -p $(OBJ_DIR)$*

# Build libft
$(LIBFT):
	@$(MAKE) -C libft > /dev/null 2>&1

# Link the final executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -s -o $(NAME) $(LIBFT) -lreadline
	@printf "\r \e[1;32mMINISHELL\e[0m compiled successfully\n"

# Compile source files into object files and place them inside the obj/ directory with subdirectories
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)$(dir $@)
	@mkdir -p $(dir $@)  # Create the directory for the object file
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean > /dev/null 2>&1
	@printf " \e[1;33mObjects Removed\n\e[0m"


# Fully clean including the executable
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean > /dev/null 2>&1
	@printf " \e[1;31mExecutable Deleted\n\e[0m"

# Rebuild everything
re: fclean all
	@printf "\r \e[1;32mRefresh OK!\e[0m\n"

.PHONY: all clean fclean re

.SILENT:
