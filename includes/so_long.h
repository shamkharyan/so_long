/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:34:16 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/28 18:28:33 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../ft_printf/ft_printf.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

# define IMAGE_WIDTH 64
# define IMAGE_HEIGHT 64

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		exit;
	int		collectable;
	t_point	coords;
	t_point	player;
	char	**map_arr;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*textures[6];
	int		tex_width;
	int		tex_height;
	t_map 	map;
}	t_game;

int		check_size(t_map *m, char *argv);
int		check_map(t_map *m);

// Utils
void	flood_fill(char **map, int *flag, int y, int x);
void	free_map(char **map, int height);
char	**copy_map(char **map, int height);

void	draw_map(t_game *game);
void	init_game(t_game *game);
int		init_map(t_map *m, char *argv);

#endif
