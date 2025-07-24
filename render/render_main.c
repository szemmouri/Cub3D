/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:29:49 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/24 17:47:02 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_debug_mode(t_game *game, t_player *p, float ray_angle,
		float fraction)
{
	int	col;

	col = 0;
	draw_map(game);
	draw_square((int)p->x, (int)p->y, 15, 0x00FF00, game);
	while (col < WIDTH)
	{
		draw_textured_line(p, game, ray_angle, col);
		ray_angle += fraction;
		col++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	render_scene(t_game *game)
{
	t_player	*p;
	float		fraction;
	float		ray_angle;
	int			col;

	p = &game->player;
	fraction = PI / 3 / WIDTH;
	ray_angle = p->angle - PI / 6;
	col = 0;
	clear_image(game);
	if (DEBUG)
	{
		render_debug_mode(game, p, ray_angle, fraction);
		return ;
	}
	while (col < WIDTH)
	{
		draw_textured_line(p, game, ray_angle, col);
		ray_angle += fraction;
		col++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	update_player_angle_and_position(t_game *game)
{
	t_player	*p;
	int			center_x;
	int			delta_x;

	p = &game->player;
	int mouse_x, mouse_y;
	center_x = WIDTH / 2;
	mlx_mouse_get_pos(game->win, &mouse_x, &mouse_y);
	delta_x = mouse_x - center_x;
	if (delta_x != 0)
	{
		p->angle += delta_x * 0.002;
		if (p->angle < 0)
			p->angle += 2 * PI;
		else if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
		mlx_mouse_move(game->win, center_x, mouse_y);
	}
	move_player(p, game);
}

int	draw_loop(t_game *game)
{
	update_player_angle_and_position(game);
	render_scene(game);
	return (0);
}
