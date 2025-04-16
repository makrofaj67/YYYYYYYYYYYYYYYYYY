#include "../../inc/so_long.h"
t_node *savefiletotmap_matrix(const char *file_path)
{
    int     fd;
    t_node  *start;
    t_node  *current;
    char    c;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    start = init_chain();
    if (!start)
    {
        close(fd);
        return (NULL);
    }
    current = start;  // Start with the first node
    
    while (read(fd, &c, 1) > 0)
    {
        t_node *new_node = create_node(c);
        if (!new_node)
            break;
            
        // Add directly to current without traversing
        current->next = new_node;
        new_node->prev = current;
        new_node->index = current->index + 1;
        
        // Move current to the new node
        current = new_node;
    }
    close(fd);
    return (start);
}

void print_linked_list(t_node *head)
{
    t_node *current;
    int i;
    
    printf("DEBUG: Linked list content (showing first 50 chars):\n");
    
    // Check if head exists
    if (!head)
    {
        printf("[Empty list]\n");
        return;
    }
    
    current = head->next;  // Skip initial node, but only if head is valid
    
    // Check if the list has any content (after the initial node)
    if (!current)
    {
        printf("[Empty list after initial node]\n");
        return;
    }
    
    // Print the content
    for (i = 0; i < 50 && current; i++)
    {
        if (current->value == '\n')
            printf("\\n");
        else
            printf("%c", current->value);
        current = current->next;
    }
    printf("\n");
}

int determine_map_width(t_node *node_list)
{
    int width = 0;
    t_node *current = node_list;
    
    // Skip the initial node (which has value 0)
    if (current)
        current = current->next;
    
    while (current && current->value != '\n')
    {
        width++;
        current = current->next;
    }
    return (width);
}

int determine_map_height(t_node *node_list)
{
    int height = 0;
    int has_content = 0;
    t_node *current = node_list;
    
    // Skip the initial node (which has value 0)
    if (current)
        current = current->next;
    
    // Skip initial newline if present
    if (current && current->value == '\n')
        current = current->next;
    
    while (current)
    {
        has_content = 1;  // We've seen at least some content
        
        if (current->value == '\n')
        {
            height++;
            // Check if there's more content after this newline
            if (current->next && current->next->value != '\n')
                has_content = 0;  // Reset for next potential line
        }
        
        current = current->next;
    }
    
    // Only add 1 if we had content after the last newline
    return height + (has_content ? 1 : 0);
}

char **allocate_grid(int height, int width)
{
    char **grid;
    int i;

    grid = (char **)malloc(sizeof(char *) * (height + 1));
    if (!grid)
        return (NULL);
    
    for (i = 0; i < height; i++)
    {
        grid[i] = (char *)malloc(sizeof(char) * (width + 1));
        if (!grid[i])
        {
            // Free previously allocated memory
            while (--i >= 0)
                free(grid[i]);
            free(grid);
            return (NULL);
        }
        // Initialize with null terminators
        grid[i][0] = '\0';
    }
    
    grid[height] = NULL; // Null-terminate the array
    return (grid);
}

char **convert_list_to_grid(t_node *node_list, int width, int height)
{
    char **grid;
    int i = 0, j = 0;
    t_node *current = node_list;

    // Skip the first node which is the init_chain node with value 0
    if (current)
        current = current->next;
    
    // Allocate memory for rows
    grid = allocate_grid(height, width);
    if (!grid)
        return (NULL);
    
    // Fill the grid
    for (i = 0; i < height; i++)
    {
        // Fill the row
        j = 0;
        while (current && j < width)
        {
            // Skip newline characters at the beginning of rows
            if (current->value == '\n')
            {
                current = current->next;
                continue;
            }
            
            grid[i][j] = current->value;
            j++;
            current = current->next;
            
            // If we encounter a newline, move to the next row
            if (current && current->value == '\n')
            {
                current = current->next;
                break;
            }
        }
        
        // If we didn't fill the entire row, report an error
        if (j < width)
        {
            // Clean up allocated memory
            for (int k = 0; k <= i; k++)
                free(grid[k]);
            free(grid);
            printf("Error: Row %d is too short (got %d chars, expected %d)\n", i, j, width);
            return (NULL);
        }
        
        // Null-terminate the string
        grid[i][j] = '\0';
    }
    
    return (grid);
}

int load_map(t_game *game, const char *file_path)
{
    t_node *node_list;
    int width, height;

    // Initialize map
    game->map = malloc(sizeof(t_map));
    if (!game->map)
        return (0);
        
    node_list = savefiletotmap_matrix(file_path);
    if (!node_list)
    {
        free(game->map);
        return (0);
    }
    print_linked_list(node_list);
    
    // Debug the linked list
    // print_node_list(node_list);
    
    width = determine_map_width(node_list);
    height = determine_map_height(node_list);
    
    // Make sure width and height are valid
    if (width <= 0 || height <= 0)
    {
        free_node_list(node_list);
        free(game->map);
        return (0);
    }
    
    game->map->grid = convert_list_to_grid(node_list, width, height);
    if (!game->map->grid)
    {
        free_node_list(node_list);
        free(game->map);
        return (0);
    }
    
    game->map->width = width;
    game->map->height = height;
    free_node_list(node_list);
    return (1);
}