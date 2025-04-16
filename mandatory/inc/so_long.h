#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
#include "../../lib/minilibx-linux/mlx.h"
#include "../../lib/ft_printf/printf/ft_printf.h"

#define TILE_SIZE 64  // You can adjust this value based on your sprite size

// Also add other useful key definitions
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363

typedef struct s_node
{
    int value;
    int index;
    struct s_node *next;
    struct s_node *prev;
} t_node;

typedef struct s_map
{
    char **grid;
    int width;
    int height;
    char *file_path;
} t_map;

typedef struct s_assets
{
    void *player;
    void *floor;
    void *collectible;
    void *exit;
    void *wall_center;
    void *wall_top;
    void *wall_bottom;
    void *wall_left;
    void *wall_right;
    void *wall_corner_tl;
    void *wall_corner_tr;
    void *wall_corner_bl;
    void *wall_corner_br;
    void *wall_inside;  // İç duvarlar için yeni alan ekleyin
} t_assets;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
} t_mlx;

typedef struct s_game
{
    t_map *map;
    t_assets assets;
    int player_x;
    int player_y;
    int total_collectibles;
    int collectibles_collected;
    int moves;
    t_mlx *mlx;
} t_game;


// Initialization & Validation
int     validate_file(int argc, char *argv[], int *fd);
int     load_map(t_game *game, const char *file_path);
int     initialize_and_validate_game(t_game *game, int argc, char *argv[]);
int     initialize_mlx(t_game *game, t_mlx *mlx);
int     load_assets(t_game *game, t_mlx *mlx);

// Map Validation
int     is_rectangular_and_enclosed(t_map *map);
int     has_valid_components(t_map *map);
int     is_map_valid(t_map *map); // Flood fill based validation
void    flood_fill(char **grid, int x, int y, int width, int height, int *collectibles, int *exit_found);
char    **copy_map_grid(t_map *map, int *collectibles, int *player_x, int *player_y);

// Game Logic
void    find_player_and_collectibles(t_game *game);
void    move_player(t_game *game, int dx, int dy);

// Rendering
void    render_map(t_game *game, t_mlx *mlx);
int     render_game(t_game *game, t_mlx *mlx);
void    *determine_wall_type(t_game *game, int x, int y);

// Event Handling
int     handle_keypress(int keycode, void *param);
// int  exit_game(t_game *game, t_mlx *mlx); // <<< OLD Line
int     exit_game(void *param);               // <<< NEW Line (Matching main.c)

// Cleanup
void    free_game_resources(t_game *game);
void    free_assets(t_game *game);
void    cleanup_mlx(t_mlx *mlx); // Keep this if used elsewhere, otherwise can remove

// Linked List Utils (if still used directly, otherwise internal)
t_node  *init_chain(void);
t_node  *create_node(unsigned char c);
t_node  *add_node(t_node *head, t_node *new_node);
void    free_node_list(t_node *head);
char    **allocate_grid(int height, int width); // Helper for map loading/copying


#endif