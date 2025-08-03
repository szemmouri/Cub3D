/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:29:49 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 13:14:33 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*get_texture_path(char *line, int j)
{
	char	*path;
	int		len;
	int		i;

	j = skip_whitespace(line, j);
	len = j;
	while (line[len] && line[len] != ' ' && line[len] != '\t'
		&& line[len] != '\n')
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		path[i++] = line[j++];
	path[i] = '\0';
	j = skip_whitespace(line, j);
	if (line[j] && line[j] != '\n')
		return (free(path), NULL);
	return (path);
}

static int	fill_direction_textures(t_texinfo *textures, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !textures->north)
		textures->north = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !textures->south)
		textures->south = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !textures->west)
		textures->west = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !textures->east)
		textures->east = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

static int	handle_color_textures(t_game *game, char *line, int j)
{
	if (line[j + 1] && (line[j + 1] == ' ' || line[j + 1] == '\t'))
	{
		if (fill_color_textures(game, &game->texinfo, line, j) == ERR)
			return (FAILURE);
		return (CONTINUE);
	}
	return (FAILURE);
}

static int	get_data(t_game *game, char **map, int i, int j)
{
	j = skip_whitespace(map[i], j);
	if (!map[i][j] || map[i][j] == '\n')
		return (FAILURE);
	if (map[i][j] == 'F' || map[i][j] == 'C')
		return (handle_color_textures(game, map[i], j));
	if ((map[i][j] == 'N' && map[i][j + 1] == 'O') ||
		(map[i][j] == 'S' && map[i][j + 1] == 'O') ||
		(map[i][j] == 'W' && map[i][j + 1] == 'E') ||
		(map[i][j] == 'E' && map[i][j + 1] == 'A'))
	{
		if (fill_direction_textures(&game->texinfo, map[i], j) == ERR)
			return (print_error(game->mapinfo.path, ERR_TEX_INVALID), FAILURE);
		return (CONTINUE);
	}
	if (ft_isdigit(map[i][j]))
	{
		if (create_map(game, map, i) == FAILURE)
			return (print_error(game->mapinfo.path, ERR_INVALID_MAP), FAILURE);
		return (SUCCESS);
	}
	return (print_error(game->mapinfo.path, "Invalid identifier"), FAILURE);
}

int	get_file_data(t_game *game, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (!map[i][0] || map[i][0] == '\n')
		{
			i++;
			continue ;
		}
		ret = get_data(game, map, i, j);
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == SUCCESS)
			return (SUCCESS);
		i++;
	}
	return (SUCCESS);
}
