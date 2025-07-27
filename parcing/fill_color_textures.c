/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:29:49 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:19:36 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_rgb_components(char **rgb_components)
{
	int		i;
	int		j;
	int		value;
	char	*trimmed;

	i = 0;
	while (rgb_components[i])
	{
		trimmed = ft_strtrim(rgb_components[i], " \t\n");
		if (!trimmed)
			return (0);
		free(rgb_components[i]);
		rgb_components[i] = trimmed;
		if (rgb_components[i][0] == '\0')
			return (0);
		j = 0;
		while (rgb_components[i][j])
			if (!ft_isdigit(rgb_components[i][j++]))
				return (0);
		value = ft_atoi(rgb_components[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	return (i == 3);
}

static int	*set_rgb_colors(char *line)
{
	char	**rgb_components;
	int		*rgb;
	int		i;
	char	*clean_line;

	if (!line)
		return (NULL);
	clean_line = ft_strtrim(line, " \t\n");
	if (!clean_line)
		return (NULL);
	rgb_components = ft_split(clean_line, ',');
	free(clean_line);
	if (!rgb_components)
		return (NULL);
	if (!validate_rgb_components(rgb_components))
		return (free_arr((void **)rgb_components), NULL);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (free_arr((void **)rgb_components), NULL);
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(rgb_components[i]);
	return (free_arr((void **)rgb_components), rgb);
}

int	fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j)
{
	if (!line[j + 1] || (line[j + 1] != ' ' && line[j + 1] != '\t'))
		return (print_error(game->mapinfo.path, ERR_FLOOR_CEILING), ERR);
	if (line[j] == 'C')
	{
		if (textures->ceiling)
			return (print_error(game->mapinfo.path, ERR_COLOR_DUPLICATE), ERR);
		textures->ceiling = set_rgb_colors(line + j + 1);
		if (!textures->ceiling)
			return (print_error(game->mapinfo.path, ERR_COLOR_CEILING), ERR);
	}
	else if (line[j] == 'F')
	{
		if (textures->floor)
			return (print_error(game->mapinfo.path, ERR_COLOR_DUPLICATE), ERR);
		textures->floor = set_rgb_colors(line + j + 1);
		if (!textures->floor)
			return (print_error(game->mapinfo.path, ERR_COLOR_FLOOR), ERR);
	}
	else
		return (print_error(game->mapinfo.path, ERR_FLOOR_CEILING), ERR);
	return (SUCCESS);
}
