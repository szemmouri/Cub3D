/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:44:35 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/27 12:04:23 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_texinfo(t_texinfo *texinfo)
{
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->west = NULL;
	texinfo->east = NULL;
	texinfo->floor = NULL;
	texinfo->ceiling = NULL;
	texinfo->hex_floor = 0;
	texinfo->hex_ceiling = 0;
	texinfo->size = 0;
	texinfo->index = 0;
	texinfo->step = 0.0;
	texinfo->pos = 0.0;
	texinfo->x = 0;
	texinfo->y = 0;
}

static void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->line_count = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->index_end_of_map = 0;
}

static void	init_player_parsing(t_player *player)
{
	player->dir = '0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->win_height = WIN_HEIGHT;
	game->win_width = WIN_WIDTH;
	init_player_parsing(&game->player);
	init_texinfo(&game->texinfo);
	game->map = NULL;
	init_mapinfo(&game->mapinfo);
	init_img(&game->minimap);
	game->texture_pixels = NULL;
	game->textures = NULL;
}
