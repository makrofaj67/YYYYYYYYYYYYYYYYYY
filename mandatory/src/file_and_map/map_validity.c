#include "../../inc/so_long.h"
int is_rectangular_and_enclosed(t_map *map)
{
    int i, j;

	printf("DEBUG: Map has %d rows\n", map->height);
for (int i = 0; i < map->height; i++) {
    printf("DEBUG: Row %d length: %zu content: '%s'\n", 
           i, strlen(map->grid[i]), map->grid[i]);
}
    for (i = 0; i < map->height; i++)
    {
		if (strlen(map->grid[i]) != map->width)
		{
			printf("Error: Map is not rectangular (row %d length is %zu, expected %d)\n", 
				   i, strlen(map->grid[i]), map->width);
			return (0);
		}

        if (i == 0 || i == map->height - 1) // İlk ve son satır
        {
            for (j = 0; j < map->width; j++)
            {
                if (map->grid[i][j] != '1')
				{printf("duvarla çevrili değil");
					return (0);} // Dik// Duvarla çevrili değil
            }
        }
        else // İlk ve son sütun
        {
            if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			{printf("duvarla çevrili değil");
				return (0);} // Dik Duvarla çevrili değil
        }
    }
    return (1);
}

int has_valid_components(t_map *map)
{
    int i, j;
    int player_count = 0, exit_count = 0, collectible_count = 0;

    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            char c = map->grid[i][j];
            if (c == 'P')
                player_count++;
            else if (c == 'E')
                exit_count++;
            else if (c == 'C')
                collectible_count++;
            else if (c != '0' && c != '1')
			{printf("geçersiz karakter");
				return (0);} // Dik
        }
    }
    return (player_count == 1 && exit_count == 1 && collectible_count >= 1);
}