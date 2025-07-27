/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:18:49 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:01:34 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_row_walls(char *row)
{
	int	i;

	i = 0;
	if (!row)
		return (FAILURE);
	while (row[i] && is_space(row[i]))
		i++;
	while (row[i])
	{
		if (!is_space(row[i]) && row[i] != '1')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	check_side_walls(char *row)
{
	int	left;
	int	right;

	left = 0;
	if (!row)
		return (FAILURE);
	right = ft_strlen(row) - 1;
	while (row[left] && is_space(row[left]))
		left++;
	if (row[left] != '1')
		return (FAILURE);
	while (right >= 0 && is_space(row[right]))
		right--;
	if (right < 0 || row[right] != '1' || left == right)
		return (FAILURE);
	return (SUCCESS);
}

int	check_map_closed(t_mapinfo *mapinfo, char **map)
{
	int	i;

	i = 1;
	if (!map || !mapinfo)
		return (FAILURE);
	if (check_row_walls(map[0]) == FAILURE)
		return (FAILURE);
	while (i < mapinfo->height - 1)
	{
		if (check_side_walls(map[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (check_row_walls(map[mapinfo->height - 1]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
