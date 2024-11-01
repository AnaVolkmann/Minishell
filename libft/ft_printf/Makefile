SRC = ft_printf.c ft_putstr.c ft_putpointer.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putpointerhexa.c
OBJ = ${SRC:.c=.o}
CC = cc 
CCFLAGS = -Werror -Wextra -Wall
NAME = libftprintf.a
RM = rm -rf

all : $(NAME)

%.o : %.c
		$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		ar rcs $@ $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
.SILENT: