/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:29:43 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/23 16:33:28 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
	if (game->bpp == 32)
		game->data[index + 3] = 0;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, color, game);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(t_game *game, int column, int start_y)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		put_pixel(column, y, game->texinfo.hex_ceiling, game);
		y++;
	}
}

void	draw_floor(t_game *game, int column, int end_y)
{
	int	y;

	y = end_y;
	while (y < HEIGHT)
	{
		put_pixel(column, y, game->texinfo.hex_floor, game);
		y++;
	}
}

void	draw_circle(int cx, int cy, int radius, int color, t_game *game)
{
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(cx + x, cy + y, color, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int		mx;
	int		my;
	int		map_w = 0, map_h;
	char	**map;
	float	scale;
	int		px;
	int		py;

	mx = MINI_MARGIN;
	my = MINI_MARGIN;
	map_w = 0, map_h = 0;
	map = game->map;
	// Calculate map width and height
	while (map[0][map_w])
		map_w++;
	while (map[map_h])
		map_h++;
	// Fill background
	for (int y = 0; y < map_h * MINI_TILE; y++)
	{
		for (int x = 0; x < map_w * MINI_TILE; x++)
		{
			put_pixel(mx + x, my + y, COLOR_MINI_BG, game);
		}
	}
	// Draw walls
	for (int y = 0; y < map_h; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			if (map[y][x] == '1')
			{
				draw_square(mx + x * MINI_TILE, my + y * MINI_TILE, MINI_TILE,
					COLOR_MINI_WALL, game);
			}
		}
	}
	// Draw player
	scale = (float)MINI_TILE / BLOCK;
	px = mx + game->player.x * scale;
	py = my + game->player.y * scale;
	draw_circle(px, py, MINI_PLAYER_SIZE, COLOR_MINI_PLAYER, game);
}
