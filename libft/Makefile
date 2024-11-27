SRC = ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_strlcat.c ft_strlen.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_memset.c \
ft_memmove.c ft_memcpy.c ft_strlcpy.c ft_strnstr.c ft_bzero.c ft_strchr.c\
ft_strrchr.c ft_calloc.c ft_memcmp.c ft_strdup.c ft_memchr.c ft_putstr_fd.c\
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_striteri.c ft_itoa.c ft_split.c ft_isspace.c\
ft_atol.c ft_factorial.c ft_fibonacci.c ft_is_prime.c ft_putnbr.c\
ft_putstr.c ft_strcmp.c ft_strchr_i.c ft_strndup.c ft_strnlen.c ft_putpointer.c\
ft_puthexa.c ft_putchar.c ft_putpointerhexa.c get_next_line.c ft_printf.c\
ft_strcompare.c\

BONUS =  ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c\
ft_lstdelone.c ft_lstsize.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
ft_find_next_prime.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c\

GNLFILES = get_next_line_utils.c 

OBJS = ${SRC:.c=.o}
OBJSBONUS = ${BONUS:.c=.o}
RM = rm -rf
CC = gcc
CFLAGS = -Werror -Wall -Wextra
NAME = libft.a

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	@echo "\033[032mLIBFT COMPILED\033[0m"

clean:
	$(RM) $(OBJS) $(OBJSBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJSBONUS) $(NAME)
	ar -vrcs $(NAME) $(OBJSBONUS)

.SILENT:

