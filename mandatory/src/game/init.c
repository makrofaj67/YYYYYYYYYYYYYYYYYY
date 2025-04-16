#include "../../inc/so_long.h"

int initialize_and_validate_game(t_game *game, int argc, char *argv[])
{
    int fd;

    if (!validate_file(argc, argv, &fd))
        return (0);

    game->map = (t_map *)malloc(sizeof(t_map));
    if (!game->map)
        return (0);

    if (!load_map(game, argv[1]))
    {
        free(game->map);
        return (write(2, "Error\nFailed to load map\n", 25), 0);
    }

    if (!is_rectangular_and_enclosed(game->map) || !has_valid_components(game->map))
    {
        free_game_resources(game);
        return (write(2, "Error\nInvalid map configuration\n", 32), 0);
    }

    return (1);
}

int initialize_mlx(t_game *game, t_mlx *mlx)
{
    game->mlx = mlx;
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        ft_printf("Error\nFailed to initialize MLX.\n");
        return (0);
    }
    
    // Pencere boyutlarını hesapla
    int win_width = game->map->width * TILE_SIZE;
    int win_height = game->map->height * TILE_SIZE;
    
    // Debug mesajı ekleyin
    ft_printf("Creating window with dimensions: %dx%d (TILE_SIZE = %d)\n", 
             win_width, win_height, TILE_SIZE);
    
    // Ekran sınırları kontrolü ekleyebilirsiniz
    int max_width = 1920;  // Örnek maksimum genişlik
    int max_height = 1080; // Örnek maksimum yükseklik
    
    if (win_width > max_width || win_height > max_height)
    {
        ft_printf("Warning: Window size (%dx%d) might be too large for your display.\n",
                 win_width, win_height);
    }
    
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_width, win_height, "so_long");
    if (!mlx->win_ptr)
    {
        ft_printf("Error\nFailed to create window.\n");
        mlx_destroy_display(mlx->mlx_ptr);
        free(mlx->mlx_ptr);
        return (0);
    }
    
    // Asset yükleme fonksiyonunu çağırın
    if (!load_assets(game, mlx))
    {
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
        mlx_destroy_display(mlx->mlx_ptr);
        free(mlx->mlx_ptr);
        return (0);
    }
    
    return (1);
}

int load_assets(t_game *game, t_mlx *mlx)
{
    int width, height;
    
    ft_printf("Loading assets...\n");
    
    // Mutlak dosya yollarını kullanın
    game->assets.player = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                           "/home/luka/Desktop/so_long/mandatory/assets/player.xpm", &width, &height);
    if (!game->assets.player)
        ft_printf("Failed to load player image!\n");
    
    game->assets.floor = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                          "/home/luka/Desktop/so_long/mandatory/assets/floor.xpm", &width, &height);
    if (!game->assets.floor)
        ft_printf("Failed to load floor image!\n");
    
    game->assets.collectible = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                "/home/luka/Desktop/so_long/mandatory/assets/collectible.xpm", &width, &height);
    if (!game->assets.collectible)
        ft_printf("Failed to load collectible image!\n");
    
    game->assets.exit = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                         "/home/luka/Desktop/so_long/mandatory/assets/exit.xpm", &width, &height);
    if (!game->assets.exit)
        ft_printf("Failed to load exit image!\n");
    
    // Diğer assetler için benzer kodlar
    game->assets.wall_center = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                "/home/luka/Desktop/so_long/mandatory/assets/topwalls.xpm", &width, &height);
    if (!game->assets.wall_center)
        ft_printf("Failed to load wall_center image!\n");
    
    game->assets.wall_top = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                              "/home/luka/Desktop/so_long/mandatory/assets/topwalls.xpm", &width, &height);
    if (!game->assets.wall_top)
        ft_printf("Failed to load wall_top image!\n");
    
    game->assets.wall_bottom = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                "/home/luka/Desktop/so_long/mandatory/assets/lowwalls.xpm", &width, &height);
    if (!game->assets.wall_bottom)
        ft_printf("Failed to load wall_bottom image!\n");
    
    game->assets.wall_left = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                               "/home/luka/Desktop/so_long/mandatory/assets/left_right_walls.xpm", &width, &height);
    if (!game->assets.wall_left)
        ft_printf("Failed to load wall_left image!\n");
    
    game->assets.wall_right = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                "/home/luka/Desktop/so_long/mandatory/assets/left_right_walls.xpm", &width, &height);
    if (!game->assets.wall_right)
        ft_printf("Failed to load wall_right image!\n");
    
    game->assets.wall_corner_tl = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                    "/home/luka/Desktop/so_long/mandatory/assets/topright-topleftwall.xpm", &width, &height);
    if (!game->assets.wall_corner_tl)
        ft_printf("Failed to load wall_corner_tl image!\n");
    
    game->assets.wall_corner_tr = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                    "/home/luka/Desktop/so_long/mandatory/assets/topright-topleftwall.xpm", &width, &height);
    if (!game->assets.wall_corner_tr)
        ft_printf("Failed to load wall_corner_tr image!\n");
    
    game->assets.wall_corner_bl = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                    "/home/luka/Desktop/so_long/mandatory/assets/botletfbotright.xpm", &width, &height);
    if (!game->assets.wall_corner_bl)
        ft_printf("Failed to load wall_corner_bl image!\n");
    
    game->assets.wall_corner_br = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                    "/home/luka/Desktop/so_long/mandatory/assets/botletfbotright.xpm", &width, &height);
    if (!game->assets.wall_corner_br)
        ft_printf("Failed to load wall_corner_br image!\n");
    
    // İç duvar görseli yükleyin
    game->assets.wall_inside = mlx_xpm_file_to_image(mlx->mlx_ptr, 
                                 "/home/luka/Desktop/so_long/mandatory/assets/blocksinsidemap.xpm", &width, &height);
    if (!game->assets.wall_inside)
        ft_printf("Failed to load wall_inside image!\n");
    
    // Hata kontrolü
    if (!game->assets.player || !game->assets.floor || 
        !game->assets.collectible || !game->assets.exit || 
        !game->assets.wall_top || !game->assets.wall_bottom ||
        !game->assets.wall_left || !game->assets.wall_right ||
        !game->assets.wall_corner_tl || !game->assets.wall_corner_tr ||
        !game->assets.wall_corner_bl || !game->assets.wall_corner_br ||
        !game->assets.wall_center || !game->assets.wall_inside)
    {
        ft_printf("Error: Some assets failed to load. Cannot continue.\n");
        return (0);
    }
    
    ft_printf("All assets loaded successfully!\n");
    return (1);
}

void find_player_and_collectibles(t_game *game)
{
    int x, y;
    
    game->total_collectibles = 0;
    game->collectibles_collected = 0;
    
    for (y = 0; y < game->map->height; y++)
    {
        for (x = 0; x < game->map->width; x++)
        {
            if (game->map->grid[y][x] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
            }
            else if (game->map->grid[y][x] == 'C')
            {
                game->total_collectibles++;
            }
        }
    }
}