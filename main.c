/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:33:28 by szemmour          #+#    #+#             */
/*   Updated: 2025/07/12 13:33:51 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int parser(t_game *game, char *fpath)
{
    if(check_file(fpath, 1) == FAILURE)
        return (clean_exit(game), FAILURE);
    parce_data(fpath, game);
    if (get_file_data(game, game->mapinfo.file) == FAILURE)
		return (free_game(game));
}

int main(int ac, char **av)
{
    t_game game;

    if(ac < 2)
        return (print_error(NULL, ERR_USAGE), 1);
    init_game(&game);
    if(!parser(&game, av[1]))
        return FAILURE;
    return SUCCESS;
}
