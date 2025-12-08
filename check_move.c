#include "cub3d.h"

int check_move_x(t_graph *graph, t_player *player, double dx)
{
	double	next_x;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_x = player->px + dx;
	map_x_left = (int)((next_x - player->radius) / IMG_PX);
	map_x_right = (int)((next_x + player->radius) / IMG_PX);
	map_y_top = (int)((player->py - player->radius) / IMG_PX);
	map_y_bottom = (int)((player->py + player->radius) / IMG_PX);
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

int check_move_y(t_graph *graph, t_player *player, double dy)
{
	double	next_y;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_y = player->py + dy;
	map_x_left = (int)((player->px - player->radius) / IMG_PX);
	map_x_right = (int)((player->px + player->radius) / IMG_PX);
	map_y_top = (int)((next_y - player->radius) / IMG_PX);
	map_y_bottom = (int)((next_y + player->radius) / IMG_PX);
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
