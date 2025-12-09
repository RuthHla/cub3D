#ifndef CUB_H
#define CUB_H

#include "../minilibx_macos/mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_data
{
    char    *tex_no;
    char    *tex_so;
    char    *tex_we;
    char    *tex_ea;
    int     floor_color;
    int     ceil_color;
    char    **map;
    int     map_w;
    int     map_h;
}   t_data;

// init/init.c
void init_data(t_data *data);

// parsing/utils.c
int  print_error(const char *msg);
int  is_empty_line(const char *s);
int  is_map_line(const char *s);
void free_map_list(t_list *lst);
int build_map_from_list(t_list *map_lines, t_data *data);
int is_space(char c);

// parsing/parse_arg.c
int check_arg(char *av);

// parsing/parse_colors.c
int parse_color(char *line, int *color);

// parsing/parse_header.c
int parse_header_line(char *line, t_data *data);
int save_map(char *path_map, t_data *data);

// parsing/parse_map.c

// parsing/parse_textures.c
int parse_texture(char *line, char **texture);







#endif