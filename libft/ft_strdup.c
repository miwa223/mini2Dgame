/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:03:58 by mmasubuc          #+#    #+#             */
/*   Updated: 2020/11/29 16:38:48 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;
	size_t	len;

	i = 0;
	while (s1[i] != '\0')
		i++;
	len = i + 1;
	dst = (char *)malloc(len);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (len-- > 0)
	{
		dst[i] = s1[i];
		i++;
	}
	return (dst);
}
