/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:50:43 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:53 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	allocate_texture_memory(t_game *game)
{
	int	i;

	game->textures = malloc(sizeof(int *) * 4);
	if (!game->textures)
		return (false);
	i = 0;
	while (i < 4)
	{
		game->textures[i] = malloc(sizeof(int) * TEXTURE_SIZE * TEXTURE_SIZE);
		if (!game->textures[i])
		{
			while (--i >= 0)
				free(game->textures[i]);
			free(game->textures);
			game->textures = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (x < 0 || y < 0)
		return (true);
	if (!game->map[y])
		return (true);
	if (x >= (int)ft_strlen(game->map[y]))
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_point a, t_point b, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = b.x - a.x;
	delta_y = b.y - a.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	get_wall_direction(float ray_x, float ray_y, float cos_angle,
		float sin_angle)
{
	int	map_x;
	int	map_y;
	int	prev_map_x;
	int	prev_map_y;

	map_x = (int)(ray_x / BLOCK);
	map_y = (int)(ray_y / BLOCK);
	prev_map_x = (int)((ray_x - cos_angle) / BLOCK);
	prev_map_y = (int)((ray_y - sin_angle) / BLOCK);
	if (map_x != prev_map_x)
	{
		if (cos_angle > 0)
			return (3);
		else
			return (2);
	}
	else if (map_y != prev_map_y)
	{
		if (sin_angle > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
