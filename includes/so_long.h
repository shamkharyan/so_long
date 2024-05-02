/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:34:16 by pshamkha          #+#    #+#             */
/*   Updated: 2024/04/30 17:40:31 by pshamkha         ###   ########.fr       */
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
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53
# define SPEED 1000

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*coin[6];
	void	*enemy;
	void	*door;
	void	*floor;
	void	*head[2];
	void	*wall;
	int		tex_width;
	int		tex_height;
	int		map_width;
	int		map_height;
	int		exit;
	int		endgame;
	int		collectable;
	int		steps;
	int		loop;
	t_point	coords;
	t_point	player;
	char	**map;
}	t_game;

int		check_size(t_game *game, char *argv);
int		check_map(t_game *game);

// Utils
void	flood_fill(char **map, int *flag, int y, int x);
void	free_map(char **map, int height);
char	**copy_map(char **map, int height);

void	draw_map(t_game *game);
void	init_game(t_game *game);
int		init_map(t_game *game, char *argv);

int		movement(int keycode, t_game *game);
int		exit_game(t_game *game, int code);
void	get_image(t_game *game, char *link, void **var);
void	draw_img(t_game *game, void *img, int x, int y);
int		animation(t_game *game);

#endif
