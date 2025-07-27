/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:02:13 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:11:28 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_map_lines(t_game *game, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
			|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (!file[i][j] || file[i][j] == '\n')
			break ;
		i++;
	}
	game->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

static int	fill_map_arr(t_mapinfo *mapinfo, char **map, int index)
{
	int	i;
	int	j;

	mapinfo->width = find_biggest_len(mapinfo, index);
	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map[i])
			return (print_error(NULL, ERR_MALLOC), FAILURE);
		while (mapinfo->file[index][j] && mapinfo->file[index][j] != '\n')
		{
			if (is_space(mapinfo->file[index][j]))
				map[i][j] = '1';
			else
				map[i][j] = mapinfo->file[index][j];
			j++;
		}
		while (j < mapinfo->width)
			map[i][j++] = '1';
		map[i++][mapinfo->width] = '\0';
		index++;
	}
	return (map[i] = NULL, SUCCESS);
}

static int	get_map_info(t_game *game, char **file, int i)
{
	game->mapinfo.height = count_map_lines(game, file, i);
	if (game->mapinfo.height < 3)
		return (print_error(game->mapinfo.path, ERR_MAP_TOO_SMALL), FAILURE);
	game->map = malloc(sizeof(char *) * (game->mapinfo.height + 1));
	if (!game->map)
		return (print_error(NULL, ERR_MALLOC), FAILURE);
	if (fill_map_arr(&game->mapinfo, game->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	create_map(t_game *game, char **file, int i)
{
	if (get_map_info(game, file, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
