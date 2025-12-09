#include "../cub.h"

static void free_data(t_data *data)
{
    int i;

    if (data->tex_no)
        free(data->tex_no);
    if (data->tex_so)
        free(data->tex_so);
    if (data->tex_we)
        free(data->tex_we);
    if (data->tex_ea)
        free(data->tex_ea);
    if(data->floor_color != 0)
        data->floor_color = 0;
    if(data->ceil_color != 0) 
        data->ceil_color = 0;
    if (data->map)
    {
        i = 0;
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
}

int main(int ac, char **av)
{
    int     i;
    t_data  data;
    int     ret;

    if (ac < 2)
    {
        printf("Usage: %s file1.cub [file2.cub ...]\n", av[0]);
        return (1);
    }

    i = 1;
    while (i < ac)
    {
        printf("=====================================\n");
        printf("Testing file: %s\n", av[i]);
        printf("=====================================\n");

        init_data(&data);

        if (!check_arg(av[i]))
        {
            printf("✅ check_arg success for %s\n\n", av[i]);
            i++;
            continue;
        }

        ret = save_map(av[i], &data);
        if (ret == 0)
        {
            printf("✅ Parsing OK pour %s\n", av[i]);
            printf("  NO: %s\n", data.tex_no);
            printf("  SO: %s\n", data.tex_so);
            printf("  WE: %s\n", data.tex_we);
            printf("  EA: %s\n", data.tex_ea);
            printf("  Floor color: %d\n", data.floor_color);
            printf("  Ceil  color: %d\n", data.ceil_color);
            printf("  Map size: %d x %d\n", data.map_h, data.map_w);
        }
        else
        {
            printf("❌ Parsing FAILED pour %s (save_map returned %d)\n",
                   av[i], ret);
        }

        free_data(&data);
        printf("\n");
        i++;
    }
    return (0);
}
