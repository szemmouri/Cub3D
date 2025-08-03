/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:51:26 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:43 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_ray_data	cast_ray(t_player *player, t_game *game, float ray_angle,
		float step)
{
	t_ray_data	ray;
	int			max_iterations;
	t_point		start;
	t_point		end;

	step = 0.6;
	max_iterations = 2000;
	ray.x = player->x;
	ray.y = player->y;
	ray.cos_angle = cos(ray_angle) * step;
	ray.sin_angle = sin(ray_angle) * step;
	while (!touch(ray.x, ray.y, game) && max_iterations > 0)
	{
		ray.x += ray.cos_angle;
		ray.y += ray.sin_angle;
		max_iterations--;
	}
	start.x = player->x;
	start.y = player->y;
	end.x = ray.x;
	end.y = ray.y;
	ray.dist = fixed_dist(start, end, game);
	if (ray.dist < 0.2)
		ray.dist = 0.2;
	return (ray);
}

static t_wall_data	calculate_wall_params(t_ray_data ray)
{
	t_wall_data	wall;

	wall.height = (BLOCK * HEIGHT) / ray.dist;
	wall.start_y = (HEIGHT - wall.height) / 2;
	wall.end_y = wall.start_y + wall.height;
	if (wall.end_y > HEIGHT)
		wall.end_y = HEIGHT;
	wall.direction = get_wall_direction(ray.x, ray.y, ray.cos_angle,
			ray.sin_angle);
	return (wall);
}

static t_texture_data	get_texture_coords(t_ray_data ray, t_wall_data wall)
{
	t_texture_data	tex;
	float			wall_hit_x;

	if (wall.direction == 0 || wall.direction == 1)
		wall_hit_x = fmod(ray.x, BLOCK);
	else
		wall_hit_x = fmod(ray.y, BLOCK);
	tex.x = (wall_hit_x / BLOCK) * TEXTURE_SIZE;
	if (tex.x < 0)
		tex.x = 0;
	if (tex.x >= TEXTURE_SIZE)
		tex.x = TEXTURE_SIZE - 1;
	if (wall.height > 0)
		tex.step = (float)TEXTURE_SIZE / wall.height;
	else
		tex.step = 1;
	if (tex.step > TEXTURE_SIZE)
		tex.step = TEXTURE_SIZE;
	if (tex.step < 0.001)
		tex.step = 0.001;
	return (tex);
}

static int	get_texture_color(t_game *game, t_wall_data wall,
		t_texture_data tex)
{
	int	tex_index;

	tex_index = (int)tex.y * TEXTURE_SIZE + (int)tex.x;
	if (tex_index >= 0 && tex_index < TEXTURE_SIZE * TEXTURE_SIZE
		&& wall.direction >= 0 && wall.direction < 4 && game->textures
		&& game->textures[wall.direction])
		return (game->textures[wall.direction][tex_index]);
	return (0x808080);
}

void	draw_textured_line(t_player *player, t_game *game, float ray_angle,
		int column)
{
	t_ray_data		ray;
	t_wall_data		wall;
	t_texture_data	tex;
	int				y;
	int				color;

	ray = cast_ray(player, game, ray_angle, 0);
	wall = calculate_wall_params(ray);
	tex = get_texture_coords(ray, wall);
	draw_ceiling(game, column, wall.start_y);
	y = wall.start_y;
	while (y < wall.end_y)
	{
		tex.y = ((y - wall.start_y) * tex.step);
		if (tex.y >= TEXTURE_SIZE)
			tex.y = TEXTURE_SIZE - 1;
		color = get_texture_color(game, wall, tex);
		put_pixel(column, y, color, game);
		y++;
	}
	draw_floor(game, column, wall.end_y);
}
