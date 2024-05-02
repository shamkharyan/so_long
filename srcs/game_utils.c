/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 17:34:49 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_map(t_game *game, char *argv)
{
	int	fd;
	int	i;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = (char **) malloc(sizeof(char *) * game->map_height);
	if (game->map == NULL)
		return (0);
	i = -1;
	while (++i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		if (game->map[i] == NULL)
		{
			free_map(game->map, i);
			return (0);
		}
	}
	close(fd);
	return (1);
}

static void	display_moves(t_game *game)
{
	char	*str;

	str = ft_itoa(game->steps);
	mlx_string_put(game->mlx, game->mlx_win, 24, 24, 0xFFFF00, "Steps: ");
	mlx_string_put(game->mlx, game->mlx_win, 100, 24, 0xFFFF00, str);
	free(str);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_img(game, game->wall, x, y);
			else if (game->map[y][x] == '0')
				draw_img(game, game->floor, x, y);
			else if (game->map[y][x] == 'E')
				draw_img(game, game->door, x, y);
			else if (game->map[y][x] == 'C')
				draw_img(game, game->coin[game->loop / SPEED], x, y);
			else if (game->map[y][x] == 'P')
				draw_img(game, game->head[game->exit], x, y);
			else if (game->map[y][x] == 'X')
				draw_img(game, game->enemy, x, y);
		}
	}
	display_moves(game);
}

void	init_game(t_game *gm)
{
	gm->mlx = mlx_init();
	gm->mlx_win = mlx_new_window(gm->mlx, gm->map_width * IMAGE_WIDTH,
			gm->map_height * IMAGE_HEIGHT, "so_long");
	gm->tex_width = IMAGE_WIDTH;
	gm->tex_height = IMAGE_HEIGHT;
	gm->steps = 0;
	gm->endgame = 0;
	gm->exit = 0;
	get_image(gm, "textures/Enemy/Enemy_0.xpm", &gm->enemy);
	get_image(gm, "textures/Floor/Floor_0.xpm", &gm->floor);
	get_image(gm, "textures/Door/Door_0.xpm", &gm->door);
	get_image(gm, "textures/Player/PLayer_0.xpm", &gm->head[0]);
	get_image(gm, "textures/Player/PLayer_1.xpm", &gm->head[1]);
	get_image(gm, "textures/Wall/Wall_0.xpm", &gm->wall);
	get_image(gm, "textures/Coin/Coin_0.xpm", &gm->coin[0]);
	get_image(gm, "textures/Coin/Coin_1.xpm", &gm->coin[1]);
	get_image(gm, "textures/Coin/Coin_2.xpm", &gm->coin[2]);
	get_image(gm, "textures/Coin/Coin_3.xpm", &gm->coin[3]);
	get_image(gm, "textures/Coin/Coin_4.xpm", &gm->coin[4]);
	get_image(gm, "textures/Coin/Coin_5.xpm", &gm->coin[5]);
}

int	animation(t_game *game)
{
	if (game->loop > 5 * SPEED)
		game->loop = 0;
	else if (game->loop % SPEED == 0)
		draw_map(game);
	game->loop++;
	return (0);
}
