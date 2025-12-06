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

int  print_error(const char *msg);
int check_arg(char *av);
int save_map(char *path_map, t_data *data);

#endif