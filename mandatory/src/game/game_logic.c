#include "../../inc/so_long.h"

// Klavye olaylarını işlemek için fonksiyon


void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;
    
    // Debug mesajı ekleyin
    ft_printf("Trying to move: dx=%d, dy=%d\n", dx, dy);
    
    // Harita sınırları kontrolü
    if (new_x < 0 || new_x >= game->map->width || new_y < 0 || new_y >= game->map->height)
        return;
    
    // Duvardan geçilemez
    if (game->map->grid[new_y][new_x] == '1')
        return;
    
    // Exit'e girme kontrolü
    if (game->map->grid[new_y][new_x] == 'E')
    {
        // Tüm collectible'lar toplandı mı kontrolü
        ft_printf("Exit reached. Collectibles: %d/%d\n", 
                 game->collectibles_collected, game->total_collectibles);
        
        if (game->collectibles_collected == game->total_collectibles)
        {
            ft_printf("All collectibles found! Game completed in %d moves.\n", game->moves + 1);
            exit_game(game);  // Oyunu bitir
            return;  // Önemli - exit_game çağrısından sonra kod çalışmaya devam etmemeli
        }
        else
        {
            ft_printf("Not enough collectibles! Find more.\n");
            return;  // Tüm collectible'lar toplanmadıysa hareketi engelle
        }
    }
    
    // Collectible toplama
    if (game->map->grid[new_y][new_x] == 'C')
    {
        game->collectibles_collected++;
        ft_printf("Collectible found! %d/%d\n", 
                 game->collectibles_collected, game->total_collectibles);
    }
    
    // Eski konumda oyuncuyu kaldır
    game->map->grid[game->player_y][game->player_x] = '0';
    
    // Yeni konuma oyuncuyu yerleştir
    game->map->grid[new_y][new_x] = 'P';
    
    // Oyuncu pozisyonunu güncelle
    game->player_x = new_x;
    game->player_y = new_y;
    
    // Hamle sayısını artır
    game->moves++;
    ft_printf("Moved to: (%d,%d), Moves: %d\n", new_x, new_y, game->moves);
    
    // Hareketten sonra ekranı güncelle
    render_game(game, game->mlx);
}