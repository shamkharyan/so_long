/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/28 19:15:17 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_map(t_map *m, char *argv)
{
	int	fd;
	int	i;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	m->map_arr = (char **) malloc(sizeof(char *) * m->height);
	if (m->map_arr == NULL)
		return (0);
	m->map_arr[0] = get_next_line(fd);
	i = 0;
	while (m->map_arr[i] != NULL)
	{
		if (m->map_arr[i++] == NULL)
		{
			free_map(m->map_arr, i);
			return (0);
		}
		m->map_arr[i] = get_next_line(fd);
	}
	return (1);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.map_arr[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures[5], x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
			else if (game->map.map_arr[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures[1], x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
			else if (game->map.map_arr[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures[2], x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
			else if (game->map.map_arr[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures[3], x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
			else if (game->map.map_arr[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures[4], x * IMAGE_WIDTH, y * IMAGE_HEIGHT);
		}
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map.width * IMAGE_WIDTH, game->map.height * IMAGE_HEIGHT, "so_long");
	game->tex_width = IMAGE_WIDTH;
	game->tex_height = IMAGE_HEIGHT;
	game->textures[0] = mlx_xpm_file_to_image(game->mlx, "textures/Enemy/Enemy_0.xpm", &game->tex_width, &game->tex_height);
	game->textures[1] = mlx_xpm_file_to_image(game->mlx, "textures/Floor/Floor_0.xpm", &game->tex_width, &game->tex_height);
	game->textures[2] = mlx_xpm_file_to_image(game->mlx, "textures/Gate/Gate_0.xpm", &game->tex_width, &game->tex_height);
	game->textures[3] = mlx_xpm_file_to_image(game->mlx, "textures/Item/Head_0.xpm", &game->tex_width, &game->tex_height);
	game->textures[4] = mlx_xpm_file_to_image(game->mlx, "textures/Player/Player_0.xpm", &game->tex_width, &game->tex_height);
	game->textures[5] = mlx_xpm_file_to_image(game->mlx, "textures/Wall/Wall_0.xpm", &game->tex_width, &game->tex_height);
}
