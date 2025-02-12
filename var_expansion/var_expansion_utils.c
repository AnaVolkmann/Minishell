#include "../minishell.h"

/**
 * @brief Processes and extracts tokens from a string.
 *
 * Iterates through the string, extracts segments, and stores them in an array.
 */
int	simple_refactor(char **array, int index, char *str, int i)
{
	int		size;

	if (!str[i] || i > sizeof_str(str, '\0'))
		return (index);
	while (str[i] && str[i] == ' ')
		i++;
	size = sizeof_str(str + i, ' ');
	if (size > sizeof_str(str + i, 34))
		size = sizeof_str(str + i, 34);
	if (size > sizeof_str(str + i, 39))
		size = sizeof_str(str + i, 39);
	if (str[i] == 34)
		size = sizeof_str(str + i + 1, 34) + 2;
	if (str[i] == 39)
		size = sizeof_str(str + i + 1, 39) + 2;
	if ((i + size) > sizeof_str(str, '\0'))
		return (index);
	array[index] = malloc(size + 1);
	if (!array[index])
		return (index);
	s_strcopy(array[index], str, i, i + size);
	return (simple_refactor(array, index + 1, str, i + size));
}

/**
 * @brief Counts special characters in a string.
 *
 * Increments the count for quotes and dollar signs in the string.
 */
int	count_special_chars(char *str, int s_q, int d_q)
{
	int i;

	i = 0;
	(void)s_q;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39
			|| str[i] == '$')
			d_q++;
		i++;
	}
	return (d_q);
}

/**
 * @brief Counts whitespace-related flaws in a string.
 *
 * Checks for improper spaces in a string while considering quotes.
 */
int	count_whitespace_flaws(char *str, int a, int b, int res)
{
	int					s_q;
	int					d_q;

	s_q = 0;
	d_q = 0;
	while (str[a])
	{
		if (str[a] == 34)
			d_q++;
		else if (str[a] == 39)
			s_q++;
		else if (!(s_q % 2) && !(d_q % 2))
		{
			if (str[a] == ' ')
			{
				if (b)
					res++;
				b = 0;
			}
			else
				b = 1;
		}
		a++;
	}
	return (res);
}

/**
 * @brief Counts total flaws in an array of strings.
 *
 * Aggregates flaws found in each string from the array.
 */
int	count_total_flaws(char **array)
{
	int			i;
	int			res;

	res = 0;
	i = 0;
	while (array[i])
	{
		res += count_whitespace_flaws(array[i], 0, 0, 0);
		res += count_special_chars(array[i], 0, 0);
		i++;
	}
	return (res);
}