/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:33:16 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/15 11:48:45 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	print_error(char *mssg, char *str)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (mssg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(mssg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 1);
}

void	print_value_error(int mssg, char *str)
{
	ft_putstr_fd("cub3D: Error: ", 2);
	ft_putnbr_fd(mssg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	clean_exit(t_game *game)
{
	if (!game)
		exit(FAILURE);
	// if (game->win && game->mlx)
	// 	mlx_destroy_window(game->mlx, game->win);
	// if (game->mlx)
	// {
	// 	mlx_destroy_display(game->mlx);
	// 	mlx_loop_end(game->mlx);
	// 	free(game->mlx);
	// }
	free_game(game);
	exit(FAILURE);
}