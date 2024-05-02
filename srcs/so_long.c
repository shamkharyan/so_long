/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:48:29 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 18:26:53 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	gm;

	if (argc != 2 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	if (!check_size(&gm, argv[1]) || !init_map(&gm, argv[1]) || !check_map(&gm))
	{
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	init_game(&gm);
	draw_map(&gm);
	mlx_hook(gm.mlx_win, 2, 1L << 0, movement, &gm);
	mlx_hook(gm.mlx_win, 17, 0, exit_game, &gm);
	mlx_loop_hook(gm.mlx, animation, &gm);
	mlx_loop(gm.mlx);
	return (0);
}
