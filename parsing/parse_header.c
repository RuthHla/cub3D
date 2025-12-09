#include "../cub.h"

int parse_header_line(char *line, t_data *data)
{
    int i;

    i = 0;
    while (is_space(line[i]))
        i++;

    // ---------- Textures ----------
    if (line[i] == 'N' && line[i + 1] == 'O'
        && is_space((unsigned char)line[i + 2]))
        return (parse_texture(line + i + 2, &data->tex_no));

    if (line[i] == 'S' && line[i + 1] == 'O'
        && is_space((unsigned char)line[i + 2]))
        return (parse_texture(line + i + 2, &data->tex_so));

    if (line[i] == 'W' && line[i + 1] == 'E'
        && is_space((unsigned char)line[i + 2]))
        return (parse_texture(line + i + 2, &data->tex_we));

    if (line[i] == 'E' && line[i + 1] == 'A'
        && is_space((unsigned char)line[i + 2]))
        return (parse_texture(line + i + 2, &data->tex_ea));

    // ---------- Couleurs ----------
    if (line[i] == 'F' && is_space((unsigned char)line[i + 1]))
        return (parse_color(line + i + 1, &data->floor_color));

    if (line[i] == 'C' && is_space((unsigned char)line[i + 1]))
        return (parse_color(line + i + 1, &data->ceil_color));

    // ---------- Identifiant invalide ----------
    return (print_error("Error\nInvalid identifier in header\n"), 0);
}

// lit .cub, save separemment header/map, stocke les infos brutes dans t_data et check uniquement l’ordre global + lignes vides 
int save_map(char *path_map, t_data *data)
{
    int     fd;
    char    *line;
    t_list  *map_lines = NULL;
    int     in_map = 0;

    fd = open(path_map, O_RDONLY);
    if (fd < 0)
        return (print_error("Error\nCannot open file\n"), 0);

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!in_map)
        {
            // --- 1) PARTIE HEADER ---
            if (is_empty_line(line))
            {
                free(line);
                continue; // lignes vides autorisées dans le header
            }
            else if (is_map_line(line))
            {
                // début de la map : à partir d'ici, plus de lignes de config
                in_map = 1;
                ft_lstadd_back(&map_lines, ft_lstnew(line));
            }
            else
            {
                // ligne de header (NO / SO / WE / EA / F / C)
                if (!parse_header_line(line, data))
                {
                    free(line);
                    free_map_list(map_lines);
                    close(fd);
                    return (0);
                }
                free(line);
            }
        }
        else
        {
            // --- 2) PARTIE MAP ---
            if (is_empty_line(line))
            {
                free(line);
                free_map_list(map_lines);
                close(fd);
                return (print_error("Error\nEmpty line inside map\n"), 0);
            }
            if (!is_map_line(line))
            {
                free(line);
                free_map_list(map_lines);
                close(fd);
                return (print_error("Error\nInvalid line inside map\n"), 0);
            }
            ft_lstadd_back(&map_lines, ft_lstnew(line));
        }
    }
    close(fd);

    if (!map_lines)
        return (print_error("Error\nMissing map\n"), 0);

    if (!data->tex_no || !data->tex_so || !data->tex_we || !data->tex_ea)
    {
        free_map_list(map_lines);
        return (print_error("Error\nMissing textures\n"), 0);
    }

    if (data->floor_color == -1 || data->ceil_color == -1)
    {
        free_map_list(map_lines);
        return (print_error("Error\nMissing colors\n"), 0);
    }

    // Construction finale de data->map
    if (!build_map_from_list(map_lines, data))
    {
        free_map_list(map_lines);
        return (print_error("Error\n(program)cannot build map from linked list\n"), 0);
    }
    free_map_list(map_lines);

    return (0);
}

