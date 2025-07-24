/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:32:17 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/23 19:43:09 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define SUCCESS 0
# define FAILURE 1
# define ERR -1
# define CONTINUE 1
# define BREAK 2
# define WHITE_SPACE_CHARS " \t\n"

// Raycasting defines
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

# define TEXTURE_SIZE 64

# define PI 3.14159265359

// size of each map cell in the minimap (in pixels)
# define MINI_TILE 10

// margin from the window borders
# define MINI_MARGIN 10

// Radius of the player dot
# define MINI_PLAYER_SIZE 4

// color constants
# define COLOR_MINI_WALL 0x0000FF   // blue
# define COLOR_MINI_BG 0x202020     // dark grey background
# define COLOR_MINI_PLAYER 0xFF0000 // green

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
	void			*img;
	int				*addr;
	int				pixel_bits;
	int				size_line;
	int				endian;
}					t_img;

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
}					t_texinfo;

typedef struct s_mapinfo
{
	int				fd;
	int				line_count;
	char			*path;
	char			**file;
	int				height;
	int				width;
	int				index_end_of_map;
}					t_mapinfo;

typedef struct s_player
{
	// Parsing fields
	char			dir;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				has_moved;
	int				move_x;
	int				move_y;
	int				rotate;
	// Rendering fields
	float			x;
	float			y;
	float			angle;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
	char			**map;
	int				**texture_pixels;
	int				**textures;
	t_player		player;
	t_mapinfo		mapinfo;
	t_texinfo		texinfo;
	t_img			minimap;
	// Rendering fields
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_game;

// Raycasting structures
typedef struct s_ray_data
{
	float			x;
	float			y;
	float			cos_angle;
	float			sin_angle;
	float			dist;
}					t_ray_data;

typedef struct s_wall_data
{
	float			height;
	int				start_y;
	int				end_y;
	int				direction;
}					t_wall_data;

typedef struct s_texture_data
{
	float			x;
	float			y;
	float			step;
}					t_texture_data;

// parcing
void				init_game(t_game *game);
void				parce_data(char *path, t_game *game);
int					get_file_data(t_game *game, char **map);
int					free_game(t_game *game);
void				print_error(char *mssg, char *str);
void				print_value_error(int mssg, char *str);
void				clean_exit(t_game *game);
void				free_arr(void **arr);
int					is_space(char c);
int					check_file(char *file_name, int cub);
int					check_map_closed(t_mapinfo *info, char **map);
size_t				find_biggest_len(t_mapinfo *map, int i);
int					fill_color_textures(t_game *game, t_texinfo *textures,
						char *line, int j);
int					create_map(t_game *game, char **file, int i);
int					check_textures_validity(t_game *game, t_texinfo *textures);
int					check_map(t_game *game, char **map);
void				init_player_direction(t_game *game);
void				init_texinfo(t_texinfo *texinfo);

// test
void				example_usage(char *map_file);
void				sync_player_data(t_game *game);
int					parser(t_game *game, char *fpath);
int					exit_game(t_game *game);

// Rendering functions
void				init_player(t_player *p);
int					key_press(int kc, t_game *game);
int					key_release(int kc, t_game *game);
void				move_player(t_player *p, t_game *g);
bool				is_wall_collision(float x, float y, t_game *g);
void				put_pixel(int x, int y, int color, t_game *game);
void				draw_square(int x, int y, int size, int color,
						t_game *game);
void				draw_map(t_game *game);
void				init_game_render(t_game *game);
void				clear_image(t_game *game);
bool				touch(float px, float py, t_game *game);
float				distance(float x, float y);
float				fixed_dist(float x1, float y1, float x2, float y2,
						t_game *game);
void				draw_textured_line(t_player *player, t_game *game,
						float ray_angle, int column);
int					get_wall_direction(float ray_x, float ray_y,
						float cos_angle, float sin_angle);
void				load_textures(t_game *game);
int					draw_loop(t_game *game);

// New organized render functions
int					setup_hooks(t_game *game);
void				draw_ceiling(t_game *game, int column, int start_y);
void				draw_floor(t_game *game, int column, int end_y);
void				fill_default_texture(int *texture);
bool				allocate_texture_memory(t_game *game);
void				draw_minimap(t_game *game);
int					mouse_move(int x, int y, t_game *game);

#endif
