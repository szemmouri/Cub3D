/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:18:49 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/15 11:08:49 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static int	check_top_or_bottom(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (FAILURE);
	while (map[i][j] == ' ' || map[i][j] == '\t'
	|| map[i][j] == '\r' || map[i][j] == '\v'
	|| map[i][j] == '\f')
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_map_closed(t_mapinfo *map, char **map_arr)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_arr, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_arr[i]) - 1;
		if (map_arr[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_arr, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
