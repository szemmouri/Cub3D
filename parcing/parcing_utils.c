/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:00:20 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/27 12:39:23 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

int	skip_whitespace(char *line, int j)
{
	while (line[j] && (line[j] == ' ' || line[j] == '\t' || line[j] == '\n'))
		j++;
	return (j);
}

size_t	find_biggest_len(t_mapinfo *map, int i)
{
	size_t	biggest_len;
	size_t	current_len;

	if (!map || !map->file || !map->file[i])
		return (0);
	biggest_len = 0;
	while (map->file[i])
	{
		current_len = ft_strlen(map->file[i]);
		if (current_len > 0 && map->file[i][current_len - 1] == '\n')
			current_len--;
		if (current_len > biggest_len)
			biggest_len = current_len;
		i++;
	}
	return (biggest_len);
}

void	print_error(char *mssg, char *str)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (mssg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(mssg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 1);
}

void	print_value_error(int mssg, char *str)
{
	ft_putstr_fd("cub3D: Error: ", 2);
	ft_putnbr_fd(mssg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
