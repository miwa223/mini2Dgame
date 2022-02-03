/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:35:16 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 12:05:24 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	is_valid_argv(int argc, char **argv)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (argc != 2)
		exit_program(INVALID_ARG);
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] == '.')
			str = &argv[1][i];
		i++;
	}
	if (!str || ft_strlen(str) != 4
		|| ft_strncmp(str, ".ber", 4) != 0)
		exit_program(INVALID_ARG);
}

void	check_character_inclusion(t_map *map)
{
	if (!ft_strchr(map->content, PLAYER) || !ft_strchr(map->content, COLLECT)
		|| !ft_strchr(map->content, EXIT))
	{
		free(map->content);
		exit_program(INVALID_MAP);
	}
}

bool	check_first_last_line(t_map *map, int i, bool is_first, bool is_last)
{
	int	j;

	j = 0;
	while ((is_first || is_last) && map->img_num.x > j)
	{
		if (map->content[i] != WALL)
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		i++;
		j++;
	}
	if (is_last && map->img_num.x == j)
		return (true);
	else
		return (false);
}

bool	count_line(t_map *map, int i, int *line_num, bool is_last)
{
	if (map->content[i] == '\n')
	{
		if (map->content[i - 1] != WALL || map->content[i + 1] != WALL)
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		(*line_num)++;
		if (*line_num == map->img_num.y - 1)
			is_last = true;
	}
	return (is_last);
}

void	is_valid_map(t_map *map)
{
	int		i;
	int		line_num;
	bool	is_first;
	bool	is_last;

	i = 0;
	line_num = 0;
	is_first = true;
	is_last = false;
	check_character_inclusion(map);
	while (map->content[i] != '\0')
	{
		if (check_first_last_line(map, i, is_first, is_last))
			return ;
		is_first = false;
		is_last = count_line(map, i, &line_num, is_last);
		if (map->content[i] != PLAYER && map->content[i] != COLLECT
			&& map->content[i] != EXIT && map->content[i] != WALL
			&& map->content[i] != SPACE && map->content[i] != '\n')
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		i++;
	}
}
