/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:41:10 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/12 13:00:04 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	lines_count(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	fill_arr(int row, int column, int i, t_game *game)
{
	char	*line;

	line = get_next_line(game->mapinfo.fd);
	while (line != NULL)
	{
		game->mapinfo.file[row] = malloc(ft_strlen(line) + 1);
		if (!game->mapinfo.file[row])
		{
			print_error(NULL, ERR_MALLOC);
			return (free_arr((void **)game->mapinfo.file));
		}
		while (line[i] != '\0')
			game->mapinfo.file[row][column++] = line[i++];
		game->mapinfo.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->mapinfo.fd);
	}
	game->mapinfo.file[row] = NULL;
}

void	parse_data(char *path, t_game *game)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game->mapinfo.line_count = lines_count(path);
	game->mapinfo.path = path;
	game->mapinfo.file = malloc(game->mapinfo.line_count + 1 * sizeof(char *));
	if (!game->mapinfo.file)
		return (print_error(NULL, ERR_MALLOC));
	game->mapinfo.fd = open(path, O_RDONLY);
	if (game->mapinfo.fd < 0)
		print_error(path, strerror(errno));
	else
	{
		fill_arr(row, column, i, game);
		close(game->mapinfo.fd);
	}
}
