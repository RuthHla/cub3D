#include "../cub.h"

void init_data(t_data *data)
{
    data->tex_no = NULL;
    data->tex_so = NULL;
    data->tex_we = NULL;
    data->tex_ea = NULL;
    data->floor_color = -1;
    data->ceil_color = -1;
    data->map = NULL;
    data->map_w = 0;
    data->map_h = 0;
    data->player_x = 0;
    data->player_y = 0;
}
