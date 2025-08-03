/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:29:43 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:19 by mel-adna         ###   ########.fr       */
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

void	draw_square(t_square sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			put_pixel(sq.x + i, sq.y + j, sq.color, sq.game);
			j++;
		}
		i++;
	}
}
