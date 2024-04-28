/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:48:29 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/28 18:32:15 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	if (!check_size(&game.map, argv[1]) || !init_map(&game.map, argv[1]) || !check_map(&game.map))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	init_map(&game.map, argv[1]);
	init_game(&game);
	draw_map(&game);
	mlx_loop(game.mlx);
	return (0);
}
