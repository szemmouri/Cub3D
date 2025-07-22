#include "includes/cub3d.h"

void print_separator(char *title)
{
    printf("\n");
    printf("=====================================\n");
    printf("         %s\n", title);
    printf("=====================================\n");
}

void print_texture_info(t_texinfo *texinfo)
{
    print_separator("TEXTURE INFORMATION");
    
    printf("North texture: %s\n", texinfo->north ? texinfo->north : "NULL");
    printf("South texture: %s\n", texinfo->south ? texinfo->south : "NULL");
    printf("West texture:  %s\n", texinfo->west ? texinfo->west : "NULL");
    printf("East texture:  %s\n", texinfo->east ? texinfo->east : "NULL");
    
    printf("\nFloor RGB: ");
    if (texinfo->floor)
        printf("(%d, %d, %d) -> HEX: 0x%06lX\n", 
               texinfo->floor[0], texinfo->floor[1], texinfo->floor[2], 
               texinfo->hex_floor);
    else
        printf("NULL\n");
    
    printf("Ceiling RGB: ");
    if (texinfo->ceiling)
        printf("(%d, %d, %d) -> HEX: 0x%06lX\n", 
               texinfo->ceiling[0], texinfo->ceiling[1], texinfo->ceiling[2], 
               texinfo->hex_ceiling);
    else
        printf("NULL\n");
}

void print_player_info(t_player *player)
{
    print_separator("PLAYER INFORMATION");
    
    printf("Player direction: %c\n", player->dir);
    printf("Player position: (%.2f, %.2f)\n", player->pos_x, player->pos_y);
    printf("Direction vector: (%.2f, %.2f)\n", player->dir_x, player->dir_y);
    printf("Camera plane: (%.2f, %.2f)\n", player->plane_x, player->plane_y);
    printf("Has moved: %s\n", player->has_moved ? "Yes" : "No");
    printf("Movement X: %d\n", player->move_x);
    printf("Movement Y: %d\n", player->move_y);
    printf("Rotation: %d\n", player->rotate);
}

void print_map_info(t_mapinfo *mapinfo)
{
    print_separator("MAP INFORMATION");
    
    printf("Map file path: %s\n", mapinfo->path ? mapinfo->path : "NULL");
    printf("Map height: %d\n", mapinfo->height);
    printf("Map width: %d\n", mapinfo->width);
    printf("Total lines in file: %d\n", mapinfo->line_count);
    printf("Map end index: %d\n", mapinfo->index_end_of_map);
}

void print_raw_file_content(t_mapinfo *mapinfo)
{
    print_separator("RAW FILE CONTENT");
    
    if (!mapinfo->file)
    {
        printf("No file content loaded!\n");
        return;
    }
    
    printf("File contains %d lines:\n", mapinfo->line_count);
    for (int i = 0; mapinfo->file[i]; i++)
    {
        printf("Line %2d: \"%s\"\n", i, mapinfo->file[i]);
    }
}

void print_parsed_map(char **map, t_mapinfo *mapinfo)
{
    print_separator("PARSED MAP");
    
    if (!map)
    {
        printf("No map data!\n");
        return;
    }
    
    printf("Map dimensions: %d x %d\n", mapinfo->width, mapinfo->height);
    printf("Map content:\n");
    
    // Print column numbers for reference
    printf("    ");
    for (int j = 0; j < mapinfo->width; j++)
        printf("%d", j % 10);
    printf("\n");
    
    // Print the map with row numbers
    for (int i = 0; map[i]; i++)
    {
        printf("%2d: ", i);
        for (int j = 0; j < mapinfo->width; j++)
        {
            char c = map[i][j];
            if (c == '\0')
                printf(".");  // Show null characters as dots
            else if (c == ' ')
                printf("_");  // Show spaces as underscores for visibility
            else
                printf("%c", c);
        }
        printf("\n");
    }
}

void print_map_validation_info(t_game *game)
{
    print_separator("MAP VALIDATION INFO");
    
    if (!game->map)
    {
        printf("✗ No map to validate\n");
        return;
    }
    
    printf("Checking map closure...\n");
    if (check_map_closed(&game->mapinfo, game->map) == SUCCESS)
        printf("✓ Map is properly closed\n");
    else
        printf("✗ Map is NOT properly closed\n");
    
    printf("\nChecking map elements...\n");
    int valid_chars = 1;
    int player_count = 0;
    
    for (int i = 0; game->map[i]; i++)
    {
        for (int j = 0; game->map[i][j]; j++)
        {
            char c = game->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
            else if (c != '0' && c != '1' && c != ' ' && c != '\0')
            {
                printf("✗ Invalid character '%c' at position (%d, %d)\n", c, i, j);
                valid_chars = 0;
            }
        }
    }
    
    if (valid_chars)
        printf("✓ All map characters are valid\n");
    
    printf("Player count: %d ", player_count);
    if (player_count == 1)
        printf("✓\n");
    else if (player_count == 0)
        printf("✗ (No player found)\n");
    else
        printf("✗ (Multiple players found)\n");
}
  

void print_memory_info(t_game *game)
{
    print_separator("MEMORY ALLOCATION INFO");
    
    printf("Game structure: %p\n", (void*)game);
    printf("Map array: %p\n", (void*)game->map);
    printf("File array: %p\n", (void*)game->mapinfo.file);
    printf("Texture paths allocated:\n");
    printf("  North: %p\n", (void*)game->texinfo.north);
    printf("  South: %p\n", (void*)game->texinfo.south);
    printf("  West: %p\n", (void*)game->texinfo.west);
    printf("  East: %p\n", (void*)game->texinfo.east);
    printf("Color arrays:\n");
    printf("  Floor: %p\n", (void*)game->texinfo.floor);
    printf("  Ceiling: %p\n", (void*)game->texinfo.ceiling);
}

// Main test function
void test_print_parsed_data(t_game *game)
{
    printf("\n");
    printf("#########################################\n");
    printf("#         CUB3D PARSING TEST           #\n");
    printf("#########################################\n");
    
    // Print all parsed information
    print_map_info(&game->mapinfo);
    print_texture_info(&game->texinfo);
    print_player_info(&game->player);
    print_raw_file_content(&game->mapinfo);
    print_parsed_map(game->map, &game->mapinfo);
    print_map_validation_info(game);
    print_memory_info(game);
    
    printf("\n");
    printf("#########################################\n");
    printf("#            TEST COMPLETE             #\n");
    printf("#########################################\n");
}

// Usage example function
void example_usage(char *map_file)
{
    t_game game;
    
    printf("Testing with file: %s\n", map_file);
    

    // Initialize game
    init_game(&game);

    if(check_file(map_file, 1) == FAILURE)
    {
        printf("❌ File check failed!\n");
        clean_exit(&game);
        return;
    }
    
    // Parse the file
    parce_data(map_file, &game);
    
    // Check if parsing was successful
    if (!game.mapinfo.file)
    {
        printf("❌ Failed to parse file data!\n");
        test_print_parsed_data(&game);
        clean_exit(&game);
        return;
    }
    
    // Get file data (textures, colors, map)
    if (get_file_data(&game, game.mapinfo.file) == SUCCESS)
    {
        // Validate textures
        if (check_textures_validity(&game, &game.texinfo) == SUCCESS)
        {
            // Check map
            if (check_map(&game, game.map) == SUCCESS)
            {
                // Initialize player direction
                init_player_direction(&game);
                
                // Print all parsed data
                printf("✅ All validation passed!\n");
                test_print_parsed_data(&game);
            }
            else
            {
                printf("❌ Map validation failed!\n");
                test_print_parsed_data(&game);  // Print anyway for debugging
            }
        }
        else
        {
            printf("❌ Texture validation failed!\n");
            test_print_parsed_data(&game);  // Print anyway for debugging
        }
    }
    else
    {
        printf("❌ Failed to parse file data!\n");
        test_print_parsed_data(&game);  // Print anyway for debugging
    }
    
    // Clean up
    clean_exit(&game);
}

int main(int ac, char **av)
{
    if(ac < 2)
        return (print_error(NULL, ERR_USAGE), 1);
    
    example_usage(av[1]);
    return SUCCESS;
}



// int parser(t_game *game, char *fpath)
// {
//     if(check_file(fpath, 1) == FAILURE)
//         return (clean_exit(game), FAILURE);
//     parce_data(fpath, game);
//     if (get_file_data(game, game->mapinfo.file) == FAILURE)
// 		return (free_game(game));
//     if (check_map(&game, game->map) == FAILURE)
//         return (free_game(game), FAILURE);
//     if (check_textures_validity(game, &game->texinfo) == FAILURE)
//         return (free_game(game), FAILURE);
//     init_player_direction(game);
//     return SUCCESS;
// }

// int main(int ac, char **av)
// {
//     t_game game;

//     if(ac < 2)
//         return (print_error(NULL, ERR_USAGE), 1);
//     init_game(&game);
//     if(parser(&game, av[1]) == FAILURE)
//         return FAILURE;
//     return SUCCESS;
// }