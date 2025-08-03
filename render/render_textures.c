/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:30:34 by mel-adna          #+#    #+#             */
/*   Updated: 2025/08/03 13:43:48 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	copy_texture_data(t_game *game, t_img *texture_imgs, int i)
{
	int	j;

	if (texture_imgs[i].img)
	{
		texture_imgs[i].addr = (int *)mlx_get_data_addr(texture_imgs[i].img,
				&texture_imgs[i].pixel_bits, &texture_imgs[i].size_line,
				&texture_imgs[i].endian);
		if (texture_imgs[i].addr)
		{
			j = 0;
			while (j < TEXTURE_SIZE * TEXTURE_SIZE)
			{
				game->textures[i][j] = texture_imgs[i].addr[j];
				j++;
			}
		}
		else
			fill_default_texture(game->textures[i]);
		mlx_destroy_image(game->mlx, texture_imgs[i].img);
	}
	else
		fill_default_texture(game->textures[i]);
}

void	fill_default_texture(int *texture)
{
	int	j;

	j = 0;
	while (j < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		texture[j] = 0x808080;
		j++;
	}
}

void	load_textures(t_game *game)
{
	t_img	texture_imgs[4];
	int		i;

	if (!allocate_texture_memory(game))
		return ;
	texture_imgs[0].img = mlx_xpm_file_to_image(game->mlx, game->texinfo.north,
			&texture_imgs[0].size_line, &texture_imgs[0].pixel_bits);
	texture_imgs[1].img = mlx_xpm_file_to_image(game->mlx, game->texinfo.south,
			&texture_imgs[1].size_line, &texture_imgs[1].pixel_bits);
	texture_imgs[2].img = mlx_xpm_file_to_image(game->mlx, game->texinfo.west,
			&texture_imgs[2].size_line, &texture_imgs[2].pixel_bits);
	texture_imgs[3].img = mlx_xpm_file_to_image(game->mlx, game->texinfo.east,
			&texture_imgs[3].size_line, &texture_imgs[3].pixel_bits);
	i = 0;
	while (i < 4)
	{
		copy_texture_data(game, texture_imgs, i);
		i++;
	}
}
