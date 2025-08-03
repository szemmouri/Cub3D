/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:57:15 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:11 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_circle(t_circle data)
{
	int	y;
	int	x;

	y = -data.radius;
	while (y <= data.radius)
	{
		x = -data.radius;
		while (x <= data.radius)
		{
			if (x * x + y * y <= data.radius * data.radius)
				put_pixel(data.cx + x, data.cy + y, data.color, data.game);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_bg(t_minimap *mini)
{
	int	x;
	int	y;

	y = 0;
	while (y < mini->map_h * MINI_TILE)
	{
		x = 0;
		while (x < mini->map_w * MINI_TILE)
		{
			put_pixel(mini->margin_x + x, mini->margin_y + y, COLOR_MINI_BG,
				mini->game);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_walls(t_minimap *mini)
{
	int			x;
	int			y;
	t_square	sq;

	y = 0;
	while (mini->map[y])
	{
		x = 0;
		while (mini->map[y][x])
		{
			if (mini->map[y][x] == '1')
			{
				sq.x = mini->margin_x + x * MINI_TILE;
				sq.y = mini->margin_y + y * MINI_TILE;
				sq.size = MINI_TILE;
				sq.color = COLOR_MINI_WALL;
				sq.game = mini->game;
				draw_square(sq);
			}
			x++;
		}
		y++;
	}
}

static void	draw_minimap_player(t_minimap *mini)
{
	float		scale;
	t_circle	circ;

	scale = (float)MINI_TILE / BLOCK;
	circ.cx = mini->margin_x + mini->game->player.x * scale;
	circ.cy = mini->margin_y + mini->game->player.y * scale;
	circ.radius = MINI_PLAYER_SIZE;
	circ.color = COLOR_MINI_PLAYER;
	circ.game = mini->game;
	draw_circle(circ);
}

void	draw_minimap(t_game *game)
{
	t_minimap	mini;
	int			i;

	mini.margin_x = MINI_MARGIN;
	mini.margin_y = MINI_MARGIN;
	mini.map = game->map;
	mini.game = game;
	mini.map_w = 0;
	mini.map_h = 0;
	i = 0;
	while (mini.map[0][i++])
		mini.map_w++;
	i = 0;
	while (mini.map[i++])
		mini.map_h++;
	draw_minimap_bg(&mini);
	draw_minimap_walls(&mini);
	draw_minimap_player(&mini);
}
