/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:35:49 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 19:38:13 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

bool	concat_map(char **map, char *line, bool first_time)
{
	char	*tmp;

	if (first_time)
	{
		*map = line;
		first_time = false;
	}
	else
	{
		tmp = *map;
		*map = ft_strjoin(*map, line);
		free(tmp);
		free(line);
	}
	tmp = *map;
	*map = ft_strjoin(*map, "\n");
	free(tmp);
	return (first_time);
}

void	get_map(char **map, int fd)
{
	char	*line;
	char	*tmp;
	int		status;
	bool	first_time;

	first_time = true;
	status = get_next_line(fd, &line);
	if (status == 0)
		*map = line;
	while (status == 1)
	{
		first_time = concat_map(map, line, first_time);
		if (get_next_line(fd, &line) == 0)
		{
			tmp = *map;
			*map = ft_strjoin(*map, line);
			free(tmp);
			free(line);
			break ;
		}
	}
}

int	count_to_eof(t_map *map, int i)
{
	bool	counted;

	counted = false;
	map->img_num.y = 0;
	while (map->content[i] != '\0')
	{
		if (map->content[i] == '\n')
		{
			if (!counted)
			{
				map->img_num.x = i;
				counted = true;
			}
			else if (counted
				&& i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
			{
				free(map->content);
				exit_program(INVALID_MAP);
			}
			map->img_num.y += 1;
		}
		i++;
	}
	return (i);
}

void	count_img_num_on_xy_axis(t_map *map)
{
	int		i;

	i = 0;
	i = count_to_eof(map, i);
	if (map->content[i - 1] != '\n')
	{
		if (i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		map->img_num.y += 1;
	}
}

void	set_map_info(char **argv, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	get_map(&data->map.content, fd);
	if (close(fd) == -1)
	{
		free(data->map.content);
		exit_program(CLOSE_FAIL);
	}
	count_img_num_on_xy_axis(&data->map);
	data->collect.count = 0;
	data->collect.total_num = 0;
	while (data->map.content[i] != '\0')
	{
		if (data->map.content[i] == COLLECT)
			data->collect.total_num++;
		i++;
	}
}
