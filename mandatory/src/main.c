#include "../inc/so_long.h"

int exit_game(void *param) 
{
    t_game *game = (t_game *)param; 

    t_mlx *mlx = game->mlx;

    // Global buffer cleanup (keep if you use g_buffer_img)
    extern void *g_buffer_img; // Assuming this is defined in render.c
    if (mlx && mlx->mlx_ptr && g_buffer_img)
    {
        mlx_destroy_image(mlx->mlx_ptr, g_buffer_img);
        g_buffer_img = NULL; // Reset pointer
    }

    // Free game assets and map data
    free_game_resources(game); // This should handle assets and map

    // Destroy window and display
    if (mlx && mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    if (mlx && mlx->mlx_ptr)
    {
        // Important: Use mlx_loop_end on Linux/X11 if available
        // mlx_loop_end(mlx->mlx_ptr); // Use if available in your MLX version

        mlx_destroy_display(mlx->mlx_ptr);
        free(mlx->mlx_ptr);
        // Set game->mlx to NULL after freeing
        game->mlx = NULL;
    }

    ft_printf("Exiting game cleanly.\n");
    exit(0); // Exit the program
    // return (0); // Unreachable after exit()
}


// --- Adjust handle_keypress ---
// Remove the redundant render_game call at the end,
// as move_player already handles rendering on success.
int handle_keypress(int keycode, void *param)
{
    t_game *game = (t_game *)param;

    // ft_printf("Key pressed: %d\n", keycode); // Optional debug

    if (keycode == 65307) // ESC key (Linux keycode)
        exit_game(game); // Pass game pointer directly
    else if (keycode == 119 || keycode == 65362) // W or Up Arrow
        move_player(game, 0, -1);
    else if (keycode == 115 || keycode == 65364) // S or Down Arrow
        move_player(game, 0, 1);
    else if (keycode == 97 || keycode == 65361)  // A or Left Arrow
        move_player(game, -1, 0);
    else if (keycode == 100 || keycode == 65363) // D or Right Arrow
        move_player(game, 1, 0);

    // REMOVED: render_game(game, game->mlx);
    // move_player calls render_game if a move actually happens.

    return (0);
}


// --- Simplified main ---
int main(int argc, char *argv[])
{
    t_game game;
    t_mlx  mlx; // Keep mlx local to main, pass its address where needed

    // Initialize game and mlx structs to zero/NULL
    ft_memset(&game, 0, sizeof(t_game));
    ft_memset(&mlx, 0, sizeof(t_mlx));
    game.mlx = &mlx; // Link mlx struct within game struct

    // 1. Validate arguments and load map data
    if (!initialize_and_validate_game(&game, argc, argv))
        return (1); // Error message printed inside function

    // 2. Initialize MLX and load assets
    // Pass the address of the local mlx struct
    if (!initialize_mlx(&game, &mlx))
    {
        free_game_resources(&game); // Free map data if MLX fails
        return (1); // Error message printed inside function
    }
    // 'game.mlx' now points to the initialized 'mlx' struct

    // 3. Find initial player position and count collectibles
    find_player_and_collectibles(&game);

    // 4. Set up event hooks
    // Pass the address of the main 'game' struct as the parameter
    mlx_hook(mlx.win_ptr, 2, 1L<<0, handle_keypress, &game); // KeyPress event
    mlx_hook(mlx.win_ptr, 17, 0, exit_game, &game);       // DestroyNotify event (window close X)

    // 5. Perform the initial render of the game state
    ft_printf("Performing initial render...\n");
    render_game(&game, &mlx); // Use the local mlx struct directly

    // 6. Start the MLX event loop
    ft_printf("Starting MLX loop...\n");
    mlx_loop(mlx.mlx_ptr);

    // Code below mlx_loop is usually unreachable because exit_game calls exit(0)
    // However, it's good practice conceptually, though cleanup should be in exit_game
    // ft_printf("MLX loop finished (should not happen in normal exit).\n");
    // free_game_resources(&game); // Cleanup is handled by exit_game
    // cleanup_mlx(&mlx); // Cleanup is handled by exit_game

    return (0); // Technically unreachable
}