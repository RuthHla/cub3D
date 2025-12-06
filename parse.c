
// int check_map(char **map, t_data *data)
// {
    // save_map
    // valid_map enregister
    // Map présente et non vide
    // Caractères autorisés : 0, 1, N, S, E, W, et espaces
    // Exactement 1 joueur (N/S/E/W)
    // Sauvegarder position + orientation du joueur
    // Map fermée / entourée de murs (pas de fuite vers l’extérieur ni vers des espaces)
    // Map = dernier bloc du fichier (plus de config après)
    // Map lue “telle qu’elle est” (respect des lignes, des espaces, etc.)
// }

#include "cub.h"

int  print_error(const char *msg)
{
    write(2, msg, ft_strlen(msg));
    return (0);
}

    //checker si bien .cub (NOM + .cub) && fichier accessible
int check_arg(char *av)
{
    int fd = 0;
    size_t len;

    if(!av)
        return (print_error("Error\nMissing map file argument\n"));
    
    len = ft_strlen(av);

    if(len < 5) // pcq au moins 1 lettre + .cub
        return (print_error("Error\nInvalid file name, expected atleast-> n.cub\n"));
    
    if(av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c' || av[len - 4] != '.')
        return(print_error("Error\nInvalid extension file name, expected -> .cub\n"));

    fd = open(av, O_RDONLY);
    if( fd == -1)
        return(print_error("Error\nCannot open file\n"));

    close(fd);
    return 1;
}

static int  is_empty_line(const char *s)
{
    int i = 0;

    if (!s)
        return (1);
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    return (s[i] == '\0' || s[i] == '\n');
}

static int  is_map_line(const char *s)
{
    int i = 0;

    // on saute les espaces au début
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    // une ligne de map doit contenir que ces caractères
    if (s[i] == '\0' || s[i] == '\n')
        return (0);
    while (s[i] && s[i] != '\n')
    {
        if (s[i] != '0' && s[i] != '1'
            && s[i] != ' ' && s[i] != '\t'
            && s[i] != 'N' && s[i] != 'S'
            && s[i] != 'E' && s[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}

int save_map(char *path_map, t_data *data)
{
    int     fd;
    char    *line;
    t_list  *map_lines = NULL; // liste chainée pour stocker temporairement
    int     in_map = 0;        // 0 = header, 1 = map

    fd = open(path_map, O_RDONLY);
    if (fd < 0)
        return (printf("Error\nCannot open file\n"), 1);

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!in_map)
        {
            if (is_empty_line(line))
            {
                free(line);
                continue;
            }
            else if (is_map_line(line))
            {
                in_map = 1;
                ft_lstadd_back(&map_lines, ft_lstnew(line));
            }
            else
            {
                if (parse_header_line(line, data) != 0)
                {
                    free(line);
                    close(fd);
                    return (1);
                }
                free(line);
            }
        }
        // 2) ON EST DANS LA MAP
        else
        {
            if (is_empty_line(line))
            {
                free(line);
                printf("Error\nEmpty line inside map\n");
                close(fd);
                return (1);
            }
            ft_lstadd_back(&map_lines, ft_lstnew(line));
        }
    }
    close(fd);

    // textures / couleurs sont bien toutes là
    if (!data->tex_no || !data->tex_so || !data->tex_we || !data->tex_ea)
        return (printf("Error\nMissing texture\n"), 1);
    // idem pour floor_color / ceil_color

    // convertir liste chainée map_lines -> data->map (char **)
    // if (build_map_from_list(map_lines, data) != 0)
    //     return (1);
    // free la liste

    return (0);
}
