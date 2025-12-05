#include "cub3d.h"

int check_move_x(t_graph *graph, double dx)
{
	double	next_x;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_x = graph->x + dx;
	map_x_left = (int)((next_x - graph->player_radius) / IMG_PX);
	map_x_right = (int)((next_x + graph->player_radius) / IMG_PX);
	map_y_top = (int)((graph->y - graph->player_radius) / IMG_PX);
	map_y_bottom = (int)((graph->y + graph->player_radius) / IMG_PX);
	if (graph->map[map_y_top][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_top][map_x_right] == '1')
			return (0);
	if (graph->map[map_y_bottom][map_x_right] == '1')
		return (0);
	return (1);
}

int check_move_y(t_graph *graph, double dy)
{
	double	next_y;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_y = graph->y + dy;
	map_x_left = (int)((graph->x - graph->player_radius) / IMG_PX);
	map_x_right = (int)((graph->x + graph->player_radius) / IMG_PX);
	map_y_top = (int)((next_y - graph->player_radius) / IMG_PX);
	map_y_bottom = (int)((next_y + graph->player_radius) / IMG_PX);
	if (graph->map[map_y_top][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_top][map_x_right] == '1')
			return (0);
	if (graph->map[map_y_bottom][map_x_right] == '1')
		return (0);
	return (1);
}
