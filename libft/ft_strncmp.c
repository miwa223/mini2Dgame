/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:20 by mmasubuc          #+#    #+#             */
/*   Updated: 2020/11/26 20:18:49 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i])
	{
		n--;
		if (s1[i] == '\0' || n == 0)
			return (0);
		i++;
	}
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
