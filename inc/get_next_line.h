/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:37:29 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 11:54:12 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# define FD_MAX 8192
# define BUFFER_SIZE 16

int		get_next_line(int fd, char **line);
int		search_newline(char **save, char **line);
int		read_buf(char **save, char *buf, int fd);
int		generate_line(char **save, char *buf, char **line, int fd);
void	free_buffer(char **buffer);
char	*ft_strchr_return_next_char(const char *s, int c);
char	*ft_strjoin_new_line(char const *s1, char const *s2);

#endif
