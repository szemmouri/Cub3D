/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:01:46 by szemmour          #+#    #+#             */
/*   Updated: 2025/08/04 10:39:16 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_elements(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	game->player.dir = '0';
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			while (is_space(map[i][j]))
				j++;
			if (!(ft_strchr("10NSEW", map[i][j])))
				return (print_error(game->mapinfo.path, ERR_INV_LETTER),
					FAILURE);
			if (ft_strchr("NSEW", map[i][j]) && game->player.dir != '0')
				return (print_error(game->mapinfo.path, ERR_NUM_PLAYER),
					FAILURE);
			if (ft_strchr("NSEW", map[i][j]) && game->player.dir == '0')
				game->player.dir = map[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_position_is_valid(t_game *game, char **map)
{
	int	i;
	int	j;

	i = (int)game->player.pos_y;
	j = (int)game->player.pos_x;
	if (ft_strlen(map[i - 1]) < (size_t)j || ft_strlen(map[i + 1]) < (size_t)j
		|| is_space(map[i][j - 1]) || is_space(map[i][j + 1]) || is_space(map[i
			- 1][j]) || is_space(map[i + 1][j]))
		return (FAILURE);
	return (SUCCESS);
}

static int	check_player_position(t_game *game, char **map)
{
	int	i;
	int	j;

	if (game->player.dir == '0')
		return (print_error(game->mapinfo.path, ERR_PLAYER_DIR), FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				game->player.pos_x = (double)j + 0.5;
				game->player.pos_y = (double)i + 0.5;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(game, map) == FAILURE)
		return (print_error(game->mapinfo.path, ERR_PLAYER_POS), FAILURE);
	return (SUCCESS);
}

static int	check_map_is_at_the_end(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (is_space(map->file[i][j]) && map->file[i][j] != '\n')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map(t_game *game, char **map)
{
	if (!game->map)
		return (print_error(game->mapinfo.path, ERR_MAP_MISSING), FAILURE);
	if (check_map_closed(&game->mapinfo, map) == FAILURE)
		return (print_error(game->mapinfo.path, ERR_MAP_NO_WALLS), FAILURE);
	if (game->mapinfo.height < 3)
		return (print_error(game->mapinfo.path, ERR_MAP_TOO_SMALL), FAILURE);
	if (check_map_elements(game, map) == FAILURE)
		return (FAILURE);
	if (check_player_position(game, map) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(&game->mapinfo) == FAILURE)
		return (print_error(game->mapinfo.path, ERR_MAP_LAST), FAILURE);
	return (SUCCESS);
}
