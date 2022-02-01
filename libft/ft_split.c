/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:03:46 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/01/26 00:49:48 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size_of_array(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && i < ft_strlen(s))
		{
			size++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (size);
}

static size_t	get_len(char const *s, char c, size_t jnum)
{
	size_t	count;

	count = 0;
	while (s[jnum] != '\0')
	{
		if (s[jnum] != c)
			count++;
		else
			return (count);
		jnum++;
	}
	return (count);
}

static void	mem_free(char **ary, size_t ary_nb)
{
	size_t	i;

	i = 0;
	while (i < ary_nb)
	{
		free(ary[i]);
		i++;
	}
	free(ary);
}

static void	split_sentence(char const *s, char c, char **array, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = -1;
	j = 0;
	while (++i < size)
	{
		while (s[j] == c)
			j++;
		array[i] = malloc(get_len((char *)s, c, j) + 1);
		if (!*array)
		{
			mem_free(array, i);
			return ;
		}
		n = 0;
		while (s[j] != c && s[j] != '\0')
			array[i][n++] = s[j++];
		array[i][n] = '\0';
	}
	array[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**array;

	size = 0;
	if (s == NULL)
		return (NULL);
	size = get_size_of_array(s, c);
	array = malloc(sizeof(char *) * size + 1);
	if (!*array)
		return (NULL);
	split_sentence(s, c, array, size);
	return (array);
}
