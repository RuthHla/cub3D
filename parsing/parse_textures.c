#include "../cub.h"

int parse_texture(char *line, char **texture)
{
    char    *path;

    if (*texture != NULL) // penser a free le reste si besoin
        return (print_error("Error\nDuplicate texture identifier\n"), 0);


    path = ft_strtrim(line, " \t\n\v\f\r");
    if (!path)
        return (print_error("Error\nMalloc failed\n"), 0);
    if (path[0] == '\0')
    {
        free(path);
        return (print_error("Error\nMissing texture path\n"), 0);
    }
    *texture = path;
    return (1);
}