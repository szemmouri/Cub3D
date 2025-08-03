/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:33:57 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:08:25 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_dir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	has_extension(const char *filename, const char *ext)
{
	size_t	len_file;
	size_t	len_ext;

	len_file = ft_strlen(filename);
	len_ext = ft_strlen(ext);
	if (len_file < len_ext)
		return (0);
	return (ft_strncmp(filename + len_file - len_ext, ext, len_ext) == 0);
}

int	check_file(char *file_name, int cub)
{
	int	fd;

	if (is_dir(file_name))
		return (print_error(file_name, ERR_FILE_IS_DIR), FAILURE);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(file_name, strerror(errno)), FAILURE);
	close(fd);
	if (cub && !has_extension(file_name, ".cub"))
		return (print_error(file_name, ERR_FILE_NOT_CUB), FAILURE);
	if (!cub && !has_extension(file_name, ".xpm"))
		return (print_error(file_name, ERR_FILE_NOT_XPM), FAILURE);
	return (SUCCESS);
}
