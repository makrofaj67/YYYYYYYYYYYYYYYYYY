#include "../../inc/so_long.h"

void free_game_resources(t_game *game)
{
    // Önce assetleri temizle
    free_assets(game);
    
    // Grid'i temizle
    if (game->map)
    {
        if (game->map->grid)
        {
            for (int y = 0; y < game->map->height; y++)
            {
                if (game->map->grid[y])
                    free(game->map->grid[y]);
            }
            free(game->map->grid);
            game->map->grid = NULL;
        }
        
        if (game->map->file_path)
            free(game->map->file_path);
            
        free(game->map);
        game->map = NULL;
    }
    
    // MLX temizleme burada zaten yapılmış olmalı, exit_game fonksiyonu içinde
}

void free_assets(t_game *game)
{
    if (game->mlx && game->mlx->mlx_ptr)
    {
        if (game->assets.player)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.player);
        if (game->assets.floor)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.floor);
        if (game->assets.collectible)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.collectible);
        if (game->assets.exit)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.exit);
            
        // Tüm duvar tiplerini temizle
        if (game->assets.wall_center)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_center);
        if (game->assets.wall_top)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_top);
        if (game->assets.wall_bottom)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_bottom);
        if (game->assets.wall_left)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_left);
        if (game->assets.wall_right)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_right);
        if (game->assets.wall_corner_tl)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_corner_tl);
        if (game->assets.wall_corner_tr)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_corner_tr);
        if (game->assets.wall_corner_bl)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_corner_bl);
        if (game->assets.wall_corner_br)
            mlx_destroy_image(game->mlx->mlx_ptr, game->assets.wall_corner_br);
    }
}

void cleanup_mlx(t_mlx *mlx)
{
    if (mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    if (mlx->mlx_ptr)
    {
        mlx_destroy_display(mlx->mlx_ptr);
        free(mlx->mlx_ptr);
    }
    // Free any textures or images here
}
