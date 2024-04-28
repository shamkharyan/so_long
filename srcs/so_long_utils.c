/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:47:09 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/28 15:14:20 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int *flag, int y, int x)
{
	if (map[y][x] == '1')
		return ;
	else if (map[y][x] == 'C' || map[y][x] == 'E')
		--(*flag);
	map[y][x] = '1';
	flood_fill(map, flag, y + 1, x);
	flood_fill(map, flag, y - 1, x);
	flood_fill(map, flag, y, x + 1);
	flood_fill(map, flag, y, x - 1);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(map[i]);
	free(map);
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	new_map = (char **) malloc(sizeof(char *) * height);
	if (new_map == NULL)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		if (new_map[i] == NULL)
		{
			free_map(new_map, i);
			return (NULL);
		}
	}
	return (new_map);
}
