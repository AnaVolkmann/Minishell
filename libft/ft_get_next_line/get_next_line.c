/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:46:55 by anavolkmann       #+#    #+#             */
/*   Updated: 2024/05/25 19:28:35 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* static variables: persistência se refere à característica de um
estado que sobrevive ao processo que o criou. Sem essa capacidade,
o estado só existiria na RAM, e seria perdido quando a RAM parasse.*/

/* @brief Pega o fd aberto e salva em uma variável "buf" o que foi
lido a partir dele. depois junta-se à variável estática cumulativa
para a persistência das informações.
 @param fd pointer para a variável estática cumulativa de
execuções anteriores 
  @return o novo valor da variavel estatica com buffer combinado
  para a persistence da info*/
char	*ft_read_left_str(int fd, char *laststr)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(laststr, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(laststr);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		laststr = ft_strjoin(laststr, buffer);
	}
	free(buffer);
	return (laststr);
}

/* @brief extrai a linha (terminando em quebra de linha e '\0' ou
so '\0')
  @param laststr o ponteiro para variavel estatica cumulativa de
execucoes anteriores da GNL
  @return a string com a linha completa terminando em uma quebra
de linha ('\n') + ('\0')*/
static char	*ft_getline(char *laststr)
{
	char	*line;
	int		len;
	int		i;

	if (!*laststr)
		return (NULL);
	len = 0;
	while (laststr[len] && laststr[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (laststr[i] && laststr[i] != '\n')
	{
		line[i] = laststr[i];
		i++;
	}
	if (laststr[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/* @brief armazena na variavel estatica cumulariva a nova variavel
atualizada com o que resta da original, MENOS a linha extraida
 @param laststr ponteiro para a variavel estatica cumulariva de
outras execucoes da GNL
  @return a nova string atualizada com o que resta da static
   original, MENOS a linha extraida */
static char	*ft_new_left_str(char *laststr)
{
	char	*str;
	int		len;
	int		i;

	if (!*laststr)
	{
		free(laststr);
		return (NULL);
	}
	len = 0;
	while (laststr[len] && laststr[len] != '\n')
		len++;
	str = malloc(sizeof(char) * (ft_strlen(laststr) - len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (laststr[len])
		str[i++] = laststr[++len];
	str[i] = '\0';
	free(laststr);
	return (str);
}

/* @brief Esta função pega um descritor de arquivo aberto e retorna
sua próxima linha. Esta função possui comportamento indefinido
ao ler um arquivo binário.
 @param fd Um descritor de arquivo
  @return uma string com a linha lida até `\n`
Se ocorrer um erro ou não houver mais nada para ler, retorna NULL.*/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*laststr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	laststr = ft_read_left_str(fd, laststr);
	if (!laststr)
		return (NULL);
	line = ft_getline(laststr);
	laststr = ft_new_left_str(laststr);
	return (line);
}

/* #include<stdio.h>
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	if (fd == -1)
	{
		printf("Error\n");
		return (0);
	}
	printf("Your fd file is %d\n", fd);
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	printf("Total of lines on file: %s", str);
	close(fd);
	return (0);
}#include <stdio.h>
#include <fcntl.h>
int main()
{
	char *a;
	int i = 0;
	int fd = open("test.txt", O_RDONLY);
	
	while (a)
	{
		a = get_next_line(fd);
		printf(" %i -> %s", i, a);
		free(a);
		i++;
	}
} */