/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:29:49 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/12 13:29:50 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	trim_component(char *str)
{
    int	i;
    int	j;
    int	len;

    // Skip leading whitespace
    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;

    // If string is only whitespace, make it empty
    if (!str[i])
    {
        str[0] = '\0';
        return;
    }

    // Move string to beginning
    if (i > 0)
    {
        j = 0;
        while (str[i])
            str[j++] = str[i++];
        str[j] = '\0';
    }

    // Remove trailing whitespace and newlines
    len = ft_strlen(str);
    i = len - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i--;

    str[i + 1] = '\0';
}

static int	validate_rgb_components(char **rgb_components)
{
    int	i;
    int	j;
    int	value;

    i = 0;
    while (rgb_components[i])
    {
        // Trim whitespace and newlines
        trim_component(rgb_components[i]);
        
        // Check if empty
        if (rgb_components[i][0] == '\0')
            return (0);

        // Check if all digits
        j = 0;
        while (rgb_components[i][j])
        {
            if (!ft_isdigit(rgb_components[i][j]))
                return (0);
            j++;
        }

        // Check value range (0-255)
        value = ft_atoi(rgb_components[i]);
        if (value < 0 || value > 255)
            return (0);

        i++;
    }

    // Ensure we have exactly 3 components
    return (i == 3);
}

static int	*set_rgb_colors(char *line)
{
    char	**rgb_components;
    int		*rgb;
    int		i;
    char	*clean_line;

    // Skip leading whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;

    // Remove trailing newline if present
    clean_line = ft_strdup(line);
    if (!clean_line)
        return (NULL);

    i = ft_strlen(clean_line) - 1;
    while (i >= 0 && (clean_line[i] == '\n' || clean_line[i] == ' ' || clean_line[i] == '\t'))
        clean_line[i--] = '\0';

    // Split by comma
    rgb_components = ft_split(clean_line, ',');
    free(clean_line);
    if (!rgb_components)
        return (NULL);

    // Validate components
    if (!validate_rgb_components(rgb_components))
    {
        free_arr((void **)rgb_components);
        return (NULL);
    }

    // Allocate RGB array
    rgb = malloc(sizeof(int) * 3);
    if (!rgb)
    {
        free_arr((void **)rgb_components);
        return (NULL);
    }

    // Convert to integers
    for (i = 0; i < 3; i++)
        rgb[i] = ft_atoi(rgb_components[i]);

    free_arr((void **)rgb_components);
    return (rgb);
}

int	fill_color_textures(t_game *game, t_texinfo *textures, char *line, int j)
{
    if (!line[j + 1] || (line[j + 1] != ' ' && line[j + 1] != '\t'))
        return (print_error(game->mapinfo.path, ERR_FLOOR_CEILING), ERR);
    
    if (line[j] == 'C')
    {
        if (textures->ceiling)
            return (print_error(game->mapinfo.path, "Duplicate ceiling color"), ERR);
        textures->ceiling = set_rgb_colors(line + j + 1);
        if (!textures->ceiling)
            return (print_error(game->mapinfo.path, ERR_COLOR_CEILING), ERR);
    }
    else if (line[j] == 'F')
    {
        if (textures->floor)
            return (print_error(game->mapinfo.path, "Duplicate floor color"), ERR);
        textures->floor = set_rgb_colors(line + j + 1);
        if (!textures->floor)
            return (print_error(game->mapinfo.path, ERR_COLOR_FLOOR), ERR);
    }
    else
        return (print_error(game->mapinfo.path, ERR_FLOOR_CEILING), ERR);
    
    return (SUCCESS);
}