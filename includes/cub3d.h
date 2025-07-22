/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:55:45 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/15 11:53:17 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
#include <stdbool.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define SUCCESS 0
# define FAILURE 1
# define ERR -1
# define CONTINUE 1
# define BREAK 2
#define WHITE_SPACE_CHARS " \t\n"

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"


// STRUCTURES
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	char		**map;
	int			**texture_pixels;
	int			**textures;
	t_player	player;
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
	t_img		minimap;
}	t_game;


// parcing
void	init_game(t_game *game);
void	parce_data(char *path, t_game *game);
int		get_file_data(t_game *game, char **map);
int		free_game(t_game *game);
void	print_error(char *mssg, char *str);
void	print_value_error(int mssg, char *str);
void	clean_exit(t_game *game);
void	free_arr(void **arr);
int 	is_space(char c);
int		check_file(char *file_name, int cub);
int		check_map_closed(t_mapinfo *info, char **map);
size_t	find_biggest_len(t_mapinfo *map, int i);
int	fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j);
int	create_map(t_game *game, char **file, int i);
int	check_textures_validity(t_game *game, t_texinfo *textures);
int	check_map(t_game *game, char **map);
void	init_player_direction(t_game *game);
void	init_texinfo(t_texinfo *texinfo);

//test
void example_usage(char *map_file);
#endif

