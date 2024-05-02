/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:34:03 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 20:04:51 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_size(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	game->map_height = 0;
	game->map_width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if (game->map_width != (int) ft_strlen(line) - 1 || line == NULL)
		{
			free(line);
			return (0);
		}
		game->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map_height > 0);
}

static int	check_borders(t_game *game)
{
	game->coords.x = 0;
	game->coords.y = 0;
	while (game->coords.y < game->map_height)
	{
		while (game->coords.x < game->map_width)
			if (game->map[game->coords.y][game->coords.x++] != '1')
				return (0);
		game->coords.y += game->map_height - 1;
		game->coords.x = 0;
	}
	game->coords.x = 0;
	game->coords.y = 0;
	while (game->coords.x < game->map_width)
	{
		while (game->coords.y < game->map_height)
			if (game->map[game->coords.y++][game->coords.x] != '1')
				return (0);
		game->coords.x += game->map_width - 1;
		game->coords.y = 0;
	}
	return (1);
}

static int	check_components(t_game *game)
{
	game->player.x = -1;
	game->exit = 0;
	game->collectable = 0;
	game->coords.y = -1;
	while (++(game->coords.y) < game->map_height)
	{
		game->coords.x = -1;
		while (++(game->coords.x) < game->map_width)
		{
			if (game->map[game->coords.y][game->coords.x] == 'P'
				&& game->player.x == -1)
				game->player = game->coords;
			else if (game->map[game->coords.y][game->coords.x] == 'C')
				++game->collectable;
			else if (game->map[game->coords.y][game->coords.x] == 'E')
				++game->exit;
			else if (game->map[game->coords.y][game->coords.x] != 'X'
				&& game->map[game->coords.y][game->coords.x] != '1'
				&& game->map[game->coords.y][game->coords.x] != '0')
				return (0);
		}
	}
	return (game->player.x != -1 && game->exit == 1 && game->collectable >= 1);
}

static int	check_path(t_game *game)
{
	int		flag;
	char	**map_copy;

	flag = game->collectable + 1;
	map_copy = copy_map(game->map, game->map_height);
	if (map_copy == NULL)
		return (0);
	flood_fill(map_copy, &flag, game->player.y, game->player.x);
	free_map(map_copy, game->map_height);
	return (!flag);
}

int	check_map(t_game *m)
{
	return (check_borders(m) && check_components(m) && check_path(m));
}
