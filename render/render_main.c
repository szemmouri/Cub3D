/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:29:49 by mel-adna          #+#    #+#             */
/*   Updated: 2025/07/23 20:19:49 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int draw_loop(t_game *game)
{
    t_player *p = &game->player;
    float fraction = PI / 3 / WIDTH;   // Field of view divided by screen width (angle per column)
    float ray_angle = p->angle - PI / 6; // Start angle of first ray (player angle - half FOV)
    int col;

    int mouse_x, mouse_y;
    // Get current mouse position relative to the window
    mlx_mouse_get_pos(game->win, &mouse_x, &mouse_y);

    int center_x = WIDTH / 2;
    // Calculate how far the mouse is from the center horizontally
    int delta_x = mouse_x - center_x;

    // If mouse moved horizontally, adjust player angle
    if (delta_x != 0)
    {
        // Rotate player angle based on mouse movement (sensitivity factor 0.002)
        p->angle += delta_x * 0.002;

        // Keep angle within 0 to 2*PI range
        if (p->angle < 0)
            p->angle += 2 * PI;
        else if (p->angle > 2 * PI)
            p->angle -= 2 * PI;

        // Reset mouse position to center of the window to allow continuous rotation
        mlx_mouse_move(game->win, center_x, mouse_y);
    }

    // Move player based on keyboard input and updated angle
    move_player(p, game);

    // Clear the current image buffer before drawing
    clear_image(game);

    if (DEBUG)
    {
        // In debug mode, draw top-down map and player square first
        draw_map(game);
        draw_square((int)p->x, (int)p->y, 15, 0x00FF00, game);

        // Cast and draw each ray for the debug view
        col = 0;
        while (col < WIDTH)
        {
            draw_textured_line(p, game, ray_angle, col);
            ray_angle += fraction;
            col++;
        }

        // Display the image to the window
        mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
        return 0;
    }

    // Normal (non-debug) mode: full 3D render
    col = 0;
    while (col < WIDTH)
    {
        draw_textured_line(p, game, ray_angle, col);
        ray_angle += fraction;
        col++;
    }

    // Draw minimap overlay on the screen
    draw_minimap(game);

    // Put the rendered image onto the window
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    return 0;
}

