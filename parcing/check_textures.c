/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:02:06 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:10:00 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	if (!rgb)
		return (FAILURE);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_value_error(rgb[i], ERR_TEX_RGB_VAL), FAILURE);
		i++;
	}
	return (SUCCESS);
}

static unsigned long	convert_rgb_to_hex(int *rgb)
{
	return (((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff));
}

int	check_textures_validity(t_game *game, t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (print_error(game->mapinfo.path, ERR_TEX_MISSING), FAILURE);
	if (!textures->floor || !textures->ceiling)
		return (print_error(game->mapinfo.path, ERR_COLOR_MISSING), FAILURE);
	if (check_file(textures->north, 0) == FAILURE || check_file(textures->south,
			0) == FAILURE || check_file(textures->west, 0) == FAILURE
		|| check_file(textures->east, 0) == FAILURE)
		return (FAILURE);
	if (check_valid_rgb(textures->floor) == FAILURE
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
