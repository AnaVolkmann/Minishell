CC = gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g

NAME = minishell
LIBFT = libft/libft.a

OBJ_DIR = obj/

SRC = ../tokenization/tokenizer.c\
../tokenization/tokenizer_utils.c\
main.c ../builtin/cd.c ../builtin/echo.c\
../builtin/env.c ../builtin/exit.c\
../builtin/export.c ../builtin/pwd.c\
../builtin/unset.c expansion.c\
init.c signal.c parser.c\
../input_validation/syntax_checker.c\


OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Default target
all: $(NAME)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build libft
$(LIBFT):
	@$(MAKE) -C libft > /dev/null 2>&1

# Link the final executable
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -s -o $(NAME) $(LIBFT) -lreadline
	@printf "\r \e[1;32mMINISHELL\e[0m compiled successfully\n"

# Compile source files into object files
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	@$(RM) $(OBJ)
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

.SILENT :
