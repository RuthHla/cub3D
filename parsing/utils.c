#include "../cub.h"

int  print_error(const char *msg)
{
    write(2, msg, ft_strlen(msg));
    return (0);
}

void free_map_list(t_list *lst)
{
    t_list *tmp;

    while (lst)
    {
        tmp = lst->next;
        free(lst->content);
        free(lst);
        lst = tmp;
    }
}

int  is_empty_line(const char *s)
{
    int i = 0;

    if (!s)
        return (1);
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    return (s[i] == '\0' || s[i] == '\n');
}

int  is_map_line(const char *s)
{
    int i = 0;

    while (is_space(s[i]))
        i++;
    if (s[i] == '\0' || s[i] == '\n')
        return (0);
    while (s[i] && s[i] != '\n')
    {
        if (s[i] != '0' && s[i] != '1'
            && !is_space(s[i])
            && s[i] != 'N' && s[i] != 'S'
            && s[i] != 'E' && s[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}

//sans le new line
static size_t  line_len(const char *s)
{
    size_t len = 0;

    if (!s)
        return (0);
    while (s[len] && s[len] != '\n')
        len++;
    return (len);
}

int build_map_from_list(t_list *map_lines, t_data *data)
{
    int     height;
    int     i;
    t_list  *tmp;
    char    *src;
    size_t  len;

    height = 0;
    tmp = map_lines;
    while (tmp)
    {
        height++;
        tmp = tmp->next;
    }
    if (height == 0)
        return (print_error("Error\nEmpty map\n"), 0);

    // 2) allouer data->map
    data->map = malloc(sizeof(char *) * (height + 1));
    if (!data->map)
        return (print_error("Error\nMalloc failed\n"), 0);

    data->map_h = height;
    data->map_w = 0;

    // 3) copier chaque ligne sans le '\n'
    i = 0;
    tmp = map_lines;
    while (tmp)
    {
        src = (char *)tmp->content;
        len = line_len(src);

        data->map[i] = malloc(len + 1);
        if (!data->map[i])
        {
            print_error("Error\nMalloc failed\n");
            // free ce qu'on a déjà alloué
            while (i > 0)
            {
                free(data->map[i - 1]);
                i--;
            }
            free(data->map);
            data->map = NULL;
            return (0);
        }
        ft_memcpy(data->map[i], src, len);
        data->map[i][len] = '\0';

        if ((int)len > data->map_w)
            data->map_w = (int)len;

        i++;
        tmp = tmp->next;
    }
    data->map[i] = NULL;

    return (1);
}

int is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
