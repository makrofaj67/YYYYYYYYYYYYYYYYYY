#include "../../inc/so_long.h"
t_node *init_chain(void)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->value = 0;
    node->index = 0;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

t_node *create_node(unsigned char c)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->value = c;
    node->index = 0;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

t_node *add_node(t_node *head, t_node *new_node)
{
    if (!head)
        return (new_node);
    while (head->next)
        head = head->next;
    head->next = new_node;
    new_node->index = head->index + 1;
    new_node->prev = head;
    return (new_node);
}

t_node *append_till_nl(t_node *start, unsigned char c)
{
    t_node *new_node;
    // Include newline characters in the linked list
    new_node = create_node(c);
    if (new_node)
        return add_node(start, new_node);
    return (NULL);
}

void free_node_list(t_node *head)
{
    t_node *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}