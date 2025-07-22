#include "../includes/cub3d.h"

int	is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
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