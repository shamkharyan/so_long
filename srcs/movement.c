/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:58:49 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 18:27:33 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	all_collected(t_game *game)
{
	game->endgame = 1;
	mlx_destroy_image(game->mlx, game->door);
	get_image(game, "textures/Door/Door_1.xpm", &game->door);
}

static void	move(t_game *game, int x, int y)
{
	if (game->map[game->player.y + y][game->player.x + x] == '0' ||
		game->map[game->player.y + y][game->player.x + x] == 'C' ||
		game->map[game->player.y + y][game->player.x + x] == 'E')
	{
		game->map[game->player.y][game->player.x] = '0'
			* !game->exit + 'E' * game->exit;
		game->exit = 0;
		if (game->map[game->player.y + y][game->player.x + x] == 'C')
			game->collectable--;
		else if (game->map[game->player.y + y][game->player.x + x] == 'E'
			&& game->collectable)
			game->exit = 1;
		else if (game->map[game->player.y + y][game->player.x + x] == 'E'
			&& !game->collectable)
			exit_game(game, 1);
		game->map[game->player.y + y][game->player.x + x] = 'P';
		game->player.y += y;
		game->player.x += x;
		game->steps++;
	}
	else if (game->map[game->player.y + y][game->player.x + x] == 'X')
		exit_game(game, 2);
	if (!game->endgame && !game->collectable)
		all_collected(game);
	draw_map(game);
}

int	exit_game(t_game *game, int code)
{
	int	i;

	free_map(game->map, game->map_height);
	mlx_destroy_image(game->mlx, game->door);
	mlx_destroy_image(game->mlx, game->enemy);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->head[0]);
	mlx_destroy_image(game->mlx, game->head[1]);
	mlx_destroy_image(game->mlx, game->wall);
	i = 0;
	while (i < 5)
		mlx_destroy_image(game->mlx, game->coin[i++]);
	mlx_destroy_window(game->mlx, game->mlx_win);
	if (code == 0)
		ft_printf("Aborted.\n");
	else if (code == 1)
		ft_printf("You win!\n");
	else if (code == 2)
		ft_printf("You lose.\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	movement(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		move(game, 0, -1);
	else if (keycode == KEY_S)
		move(game, 0, 1);
	else if (keycode == KEY_A)
		move(game, -1, 0);
	else if (keycode == KEY_D)
		move(game, 1, 0);
	else if (keycode == KEY_ESC)
		exit_game(game, 0);
	return (0);
}
