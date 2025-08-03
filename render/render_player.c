/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:30:04 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:39 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	safe_move_collision_check(float x, float y, t_game *g)
{
	float	buffer;

	buffer = 15;
	if (is_wall_collision(x + buffer, y + buffer, g) || is_wall_collision(x
			- buffer, y + buffer, g) || is_wall_collision(x + buffer, y
			- buffer, g) || is_wall_collision(x - buffer, y - buffer, g))
		return (true);
	if (is_wall_collision(x, y, g))
		return (true);
	return (false);
}

static void	try_move_to(t_player *p, t_game *g, float nx, float ny)
{
	float	old_x;
	float	old_y;

	old_x = p->x;
	old_y = p->y;
	if (!safe_move_collision_check(nx, ny, g))
	{
		p->x = nx;
		p->y = ny;
		return ;
	}
	if (!safe_move_collision_check(nx, old_y, g))
	{
		p->x = nx;
		return ;
	}
	if (!safe_move_collision_check(old_x, ny, g))
	{
		p->y = ny;
		return ;
	}
}

static void	handle_movement(t_player *p, t_game *g, float ca, float sa)
{
	float	spd;
	float	nx;
	float	ny;

	spd = 3;
	if (p->key_up)
	{
		nx = p->x + ca * spd;
		ny = p->y + sa * spd;
		try_move_to(p, g, nx, ny);
	}
	if (p->key_down)
	{
		nx = p->x - ca * spd;
		ny = p->y - sa * spd;
		try_move_to(p, g, nx, ny);
	}
}

static void	handle_strafe(t_player *p, t_game *g, float ca, float sa)
{
	float	spd;
	float	nx;
	float	ny;

	spd = 2;
	if (p->key_left)
	{
		nx = p->x - sa * spd;
		ny = p->y + ca * spd;
		try_move_to(p, g, nx, ny);
	}
	if (p->key_right)
	{
		nx = p->x + sa * spd;
		ny = p->y - ca * spd;
		try_move_to(p, g, nx, ny);
	}
}

void	move_player(t_player *p, t_game *g)
{
	float	rs;
	float	ca;
	float	sa;

	rs = 0.03;
	if (p->left_rotate)
		p->angle -= rs;
	if (p->right_rotate)
		p->angle += rs;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
	ca = cos(p->angle);
	sa = sin(p->angle);
	handle_movement(p, g, ca, sa);
	handle_strafe(p, g, ca, sa);
}
