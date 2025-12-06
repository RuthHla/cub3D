#include "libft.h"
#include <stdlib.h>

// permet dajouter du contenu a la var content de la liste chainee
t_list *ft_lstnew(void *content)
{
    t_list *new_node;

    new_node = (t_list*) malloc (sizeof(t_list));
    if(!new_node)
        return NULL;

    new_node -> content = content;
    new_node -> next = NULL;

    return new_node;
}