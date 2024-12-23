/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/12/03 12:14:43 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include "ft_printf.h"

/*.....................LIST.....................*/

typedef struct s_list
{
	int				number;
	struct s_list	*target;
	struct s_list	*prev;
	struct s_list	*next;
	void			*content;
}	t_list;

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
 */
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*.....................CHARS.....................*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		is_space(char *line);

/*.....................STRING.....................*/

char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr_i(const char *s, int c);
char	*ft_strndup(const char *src, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
int		ft_strcompare(char *s_1, char *s_2, int max);
void	ft_strcopy(char *s_1, char *s_2, int start, int end);

/*.....................MEMORY.....................*/

void	*ft_calloc(size_t num, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	ft_bzero(void *s, size_t n);

/*.....................INTEGERS.....................*/

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);

/*........................FD..........................*/

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

/*..........................CALC.......................*/

int		ft_sqrt(int nb);
int		ft_is_prime(int nb);
int		ft_find_next_prime(int nb);
int		ft_fibonacci(int index);
int		ft_recursive_factorial(int nb);

/*.........................PRINTF.........................*/

int		ft_putchar(int c);
int		ft_printf(const char *str, ...);
int		ft_puthexa(unsigned int nbr, const char c);
int		ft_putnbr(int nbr, int u);
int		ft_putpointer(unsigned long nbr);
int		ft_putpointerhexa(unsigned long nbr, const char c);
int		ft_putstr(char *str);

/*.....................GET_NEXT_LINE......................*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);

#endif