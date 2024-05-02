/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:47:09 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 17:39:46 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int *flag, int y, int x)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
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
		free(map[i++]);
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

void	get_image(t_game *game, char *link, void **var)
{
	*var = mlx_xpm_file_to_image(game->mlx,
			link, &game->tex_width, &game->tex_height);
}

void	draw_img(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, img,
		x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
}
