/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:07:11 by szemmour          #+#    #+#             */
/*   Updated: 2025/08/03 13:42:10 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	sync_player_data(t_game *game)
{
	game->player.x = game->player.pos_x * BLOCK;
	game->player.y = game->player.pos_y * BLOCK;
	if (game->player.dir == 'N')
		game->player.angle = PI * 1.5;
	else if (game->player.dir == 'S')
		game->player.angle = PI * 0.5;
	else if (game->player.dir == 'E')
		game->player.angle = 0;
	else if (game->player.dir == 'W')
		game->player.angle = PI;
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

int	exit_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	exit(0);
	return (0);
}

int	parser(t_game *game, char *fpath)
{
	if (check_file(fpath, 1) == FAILURE)
		return (FAILURE);
	parce_data(fpath, game);
	if (get_file_data(game, game->mapinfo.file) == FAILURE)
		return (free_game(game));
	if (check_map(game, game->map) == FAILURE)
		return (free_game(game), FAILURE);
	if (check_textures_validity(game, &game->texinfo) == FAILURE)
		return (free_game(game), FAILURE);
	init_player_direction(game);
	return (SUCCESS);
}

void	ll(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;

	ll();
	if (ac < 2)
		return (print_error(NULL, ERR_USAGE), 1);
	init_game(&game);
	if (parser(&game, av[1]) == FAILURE)
		return (FAILURE);
	init_game_render(&game);
	sync_player_data(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, exit_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (SUCCESS);
}
