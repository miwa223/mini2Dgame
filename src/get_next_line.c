/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:35:40 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 12:12:48 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	search_newline(char **save, char **line)
{
	char	*after_newline;
	char	*tmp;

	if (*save)
	{
		after_newline = ft_strchr_return_next_char(*save, '\n');
		if (after_newline)
		{
			*line = ft_substr(*save, 0, after_newline - *save - 1);
			if (!*line)
			{
				free_buffer(save);
				exit_program(MALLOC_FAIL);
			}
			tmp = *save;
			*save = ft_strdup(after_newline);
			free_buffer(&tmp);
			if (!*save)
				exit_program(MALLOC_FAIL);
			return (1);
		}
		*line = *save;
		*save = NULL;
	}
	return (0);
}

int	read_buf(char **save, char *buf, int fd)
{
	ssize_t	i;
	char	*after_newline;

	i = read(fd, buf, BUFFER_SIZE);
	if (i == -1)
		exit_program(READ_FAIL);
	if (i == 0)
		return (0);
	buf[i] = '\0';
	after_newline = ft_strchr_return_next_char(buf, '\n');
	i = 0;
	if (after_newline)
	{
		*save = ft_strdup(after_newline);
		if (!*save)
			exit_program(MALLOC_FAIL);
		while (buf[i] != '\n' && i < BUFFER_SIZE)
			i++;
		buf[i] = '\0';
	}
	return (1);
}

int	generate_line(char **save, char *buf, char **line, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (!*save)
	{
		if (read_buf(save, buf, fd) == 0)
			return (0);
		if (!*line)
			*line = ft_strdup(buf);
		else if (*line)
		{
			tmp = *line;
			*line = ft_strjoin_new_line(*line, buf);
			free_buffer(&tmp);
		}
		if (!*line)
		{
			free_buffer(save);
			exit_program(MALLOC_FAIL);
		}
	}
	return (1);
}

void	free_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*save[FD_MAX];
	char		*buf;
	ssize_t		status;

	*line = NULL;
	buf = NULL;
	if (fd < 0 || fd > FD_MAX || !line)
		exit_program(OPEN_FAIL);
	if (search_newline(&save[fd], line) == 1)
		return (1);
	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		exit_program(MALLOC_FAIL);
	status = generate_line(&save[fd], buf, line, fd);
	free_buffer(&buf);
	if (status == 0 && *line == NULL)
	{
		*line = (char *)malloc(1);
		if (!*line)
			exit_program(MALLOC_FAIL);
		**line = '\0';
	}
	return (status);
}
