/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:34:03 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/28 18:45:39 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_size(t_map *m, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	m->height = 0;
	m->width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if (m->width != (int) ft_strlen(line) - 1 || line == NULL)
			return (0);
		m->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	check_borders(t_map *m)
{
	m->coords.x = 0;
	m->coords.y = 0;
	while (m->coords.y < m->height)
	{
		while (m->coords.x < m->width)
			if (m->map_arr[m->coords.y][m->coords.x++] != '1')
				return (0);
		m->coords.y += m->height - 1;
		m->coords.x = 0;
	}
	m->coords.x = 0;
	m->coords.y = 0;
	while (m->coords.x < m->width)
	{
		while (m->coords.y < m->height)
			if (m->map_arr[m->coords.y++][m->coords.x] != '1')
				return (0);
		m->coords.x += m->width - 1;
		m->coords.y = 0;
	}
	return (1);
}

static int	check_components(t_map *m)
{
	m->player.x = -1;
	m->player.y = -1;
	m->exit = 0;
	m->collectable = 0;
	m->coords.y = -1;
	while (++(m->coords.y) < m->height)
	{
		m->coords.x = -1;
		while (++(m->coords.x) < m->width)
		{
			if (m->map_arr[m->coords.y][m->coords.x] == 'P')
				m->player = m->coords;
			else if (m->map_arr[m->coords.y][m->coords.x] == 'C')
				++m->collectable;
			else if (m->map_arr[m->coords.y][m->coords.x] == 'E')
				++m->exit;
			else if (!(m->map_arr[m->coords.y][m->coords.x] == '1')
				&& !(m->map_arr[m->coords.y][m->coords.x] == '0'))
				return (0);
		}
	}
	return (m->player.x != -1 && m->exit == 1 && m->collectable >= 1);
}

static int	check_path(t_map *m)
{
	int		flag;
	char	**map_copy;

	flag = m->exit + m->collectable;
	map_copy = copy_map(m->map_arr, m->height);
	if (map_copy == NULL)
		return (0);
	flood_fill(map_copy, &flag, m->player.y, m->player.x);
	return (!flag);
}

int	check_map(t_map *m)
{
	return (check_borders(m) && check_components(m) && check_path(m));
}


