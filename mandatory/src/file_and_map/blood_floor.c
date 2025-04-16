#include "../../inc/so_long.h"

void flood_fill(char **grid, int x, int y, int width, int height, int *collectibles, int *exit_found)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    if (grid[y][x] == '1' || grid[y][x] == 'V') // 'V' ziyaret edilmiş anlamında
        return;

    if (grid[y][x] == 'C')
        (*collectibles)--;
    if (grid[y][x] == 'E')
        *exit_found = 1;

    grid[y][x] = 'V'; // Ziyaret edildi olarak işaretle
    flood_fill(grid, x + 1, y, width, height, collectibles, exit_found);
    flood_fill(grid, x - 1, y, width, height, collectibles, exit_found);
    flood_fill(grid, x, y + 1, width, height, collectibles, exit_found);
    flood_fill(grid, x, y - 1, width, height, collectibles, exit_found);
}

char **copy_map_grid(t_map *map, int *collectibles, int *player_x, int *player_y)
{
    char **grid_copy = allocate_grid(map->height, map->width);
    if (!grid_copy)
        return (NULL);
    *collectibles = 0;
    *player_x = -1;
    *player_y = -1;
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            grid_copy[i][j] = map->grid[i][j];
            if (map->grid[i][j] == 'C')
                (*collectibles)++;
            if (map->grid[i][j] == 'P')
            {
                *player_x = j;
                *player_y = i;
            }
        }
    }
    return (grid_copy);
}

int is_map_valid(t_map *map)
{
    int collectibles, exit_found = 0;
    int player_x, player_y;

    char **grid_copy = copy_map_grid(map, &collectibles, &player_x, &player_y);
    if (!grid_copy)
        return (0);
    flood_fill(grid_copy, player_x, player_y, map->width, map->height, &collectibles, &exit_found);
    for (int i = 0; i < map->height; i++)
        free(grid_copy[i]);
    free(grid_copy);
    return (collectibles == 0 && exit_found);
}