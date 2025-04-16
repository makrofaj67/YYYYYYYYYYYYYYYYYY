#include "../../inc/so_long.h"

// render.c içinde bir global değişken oluşturun (veya t_mlx yapısına ekleyin)
void *g_buffer_img = NULL;
int *g_buffer_data = NULL;

// Duvar tipini belirleme fonksiyonu
void *determine_wall_type(t_game *game, int x, int y)
{
    // Null pointer kontrolü
    if (!game || !game->map)
        return (NULL);
    
    // Debug ekleyin
    static int first_wall = 1;
    if (first_wall)
    {
        ft_printf("First wall determination...\n");
        first_wall = 0;
    }

    // Harita sınırlarını kontrol et
    int is_top = (y == 0);
    int is_bottom = (y == game->map->height - 1);
    int is_left = (x == 0);
    int is_right = (x == game->map->width - 1);
    
    // İç duvar kontrolü (haritanın kenarında değilse)
    if (!is_top && !is_bottom && !is_left && !is_right)
        return (game->assets.wall_inside);
    
    // Köşe duvarları
    if (is_top && is_left)
        return (game->assets.wall_corner_tl);
    if (is_top && is_right)
        return (game->assets.wall_corner_tr);
    if (is_bottom && is_left)
        return (game->assets.wall_corner_bl);
    if (is_bottom && is_right)
        return (game->assets.wall_corner_br);
    
    // Kenar duvarları
    if (is_top)
        return (game->assets.wall_top);
    if (is_bottom)
        return (game->assets.wall_bottom);
    if (is_left)
        return (game->assets.wall_left);
    if (is_right)
        return (game->assets.wall_right);
    
    // İç duvar görseli (varsayılan)
    return (game->assets.wall_inside);
}

// Harita render fonksiyonu
void render_map(t_game *game, t_mlx *mlx)
{
    int x, y;
    
    // Debug mesajını tamamen kaldırın veya sadece ilk çağrıda gösterin
    static int first_map_render = 1;
    if (first_map_render)
    {
        ft_printf("First map render call...\n");
        ft_printf("Map dimensions: %dx%d\n", game->map->width, game->map->height);
        first_map_render = 0;
    }
    
    // İlk geçişte, tüm zemin karelerini çiz
    for (y = 0; y < game->map->height; y++)
    {
        for (x = 0; x < game->map->width; x++)
        {
            // Her kare için önce zemini çiz (her zaman)
            mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
                                  game->assets.floor, 
                                  x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    
    // İkinci geçişte, diğer öğeleri çiz (duvarlar, collectible, exit, player)
    for (y = 0; y < game->map->height; y++)
    {
        for (x = 0; x < game->map->width; x++)
        {
            // Artık zemini burada çizmiyoruz, çünkü zaten çizdik
            
            // Diğer elemanları çiz
            if (game->map->grid[y][x] == '1')
            {
                void *wall_img = determine_wall_type(game, x, y);
                if (wall_img)  // NULL pointer kontrolü ekleyin
                {
                    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
                                          wall_img, 
                                          x * TILE_SIZE, y * TILE_SIZE);
                }
            }
            else if (game->map->grid[y][x] == 'C')
            {
                mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
                                      game->assets.collectible, 
                                      x * TILE_SIZE, y * TILE_SIZE);
            }
            else if (game->map->grid[y][x] == 'E')
            {
                mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
                                      game->assets.exit, 
                                      x * TILE_SIZE, y * TILE_SIZE);
            }
            else if (game->map->grid[y][x] == 'P')
            {
                mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
                                      game->assets.player, 
                                      x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}

// render.c içinde
int render_game(t_game *game, t_mlx *mlx)
{
    // Sol üst köşedeki flicker sorununu çözmek için özel işlem
    void *first_tile = NULL;
    
    if (game->map->grid[0][0] == '1')
        first_tile = determine_wall_type(game, 0, 0);
    else if (game->map->grid[0][0] == 'P')
        first_tile = game->assets.player;
    else if (game->map->grid[0][0] == 'C')
        first_tile = game->assets.collectible;
    else if (game->map->grid[0][0] == 'E')
        first_tile = game->assets.exit;
    else
        first_tile = game->assets.floor;
        
    // Normal render işlemi
    render_map(game, mlx);
    
    // Sol üst köşeyi tekrar çizin
    if (first_tile)
    {
        // Önce zemini çizin
        if (game->map->grid[0][0] != '0')
            mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, game->assets.floor, 0, 0);
            
        // Sonra öğeyi çizin
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, first_tile, 0, 0);
    }
    
    return (0);
}
