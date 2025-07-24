/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:30:04 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/23 20:12:57 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int kc, t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (kc == ESC)
		return (exit_game(game));
	if (kc == W)
		p->key_up = true;
	if (kc == S)
		p->key_down = true;
	if (kc == A)
		p->key_left = true;
	if (kc == D)
		p->key_right = true;
	if (kc == LEFT)
		p->left_rotate = true;
	if (kc == RIGHT)
		p->right_rotate = true;
	return (0);
}

int	key_release(int kc, t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (kc == W)
		p->key_up = false;
	if (kc == S)
		p->key_down = false;
	if (kc == A)
		p->key_left = false;
	if (kc == D)
		p->key_right = false;
	if (kc == LEFT)
		p->left_rotate = false;
	if (kc == RIGHT)
		p->right_rotate = false;
	return (0);
}

bool	is_wall_collision(float x, float y, t_game *g)
{
	int	mx;
	int	my;

	mx = (int)(x / BLOCK);
	my = (int)(y / BLOCK);
	return (mx < 0 || my < 0 || g->map[my][mx] == '1');
}

int mouse_move(int x, int y, t_game *game)
{
    int center_x = WIDTH / 2;
    int delta_x = x - center_x;

    if (delta_x != 0)
    {
        game->player.angle += delta_x * 0.002;
        if (game->player.angle < 0)
            game->player.angle += 2 * PI;
        else if (game->player.angle > 2 * PI)
            game->player.angle -= 2 * PI;
        mlx_mouse_move(game->win, center_x, y);
    }
    (void)y;
    return (0);
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
		if (!is_wall_collision(nx, ny, g))
		{
			p->x = nx;
			p->y = ny;
		}
	}
	if (p->key_down)
	{
		nx = p->x - ca * spd;
		ny = p->y - sa * spd;
		if (!is_wall_collision(nx, ny, g))
		{
			p->x = nx;
			p->y = ny;
		}
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
		if (!is_wall_collision(nx, ny, g))
		{
			p->x = nx;
			p->y = ny;
		}
	}
	if (p->key_right)
	{
		nx = p->x + sa * spd;
		ny = p->y - ca * spd;
		if (!is_wall_collision(nx, ny, g))
		{
			p->x = nx;
			p->y = ny;
		}
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
