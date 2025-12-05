#include "cub3d.h"

void	update_direction_vectors(t_graph *graph)
{
	graph->pdx = cos(graph->pa) * 5;
	graph->pdy = sin(graph->pa) * 5;
	graph->dirX = cos(graph->pa);
	graph->dirY = sin(graph->pa);
}

int	look_left(t_graph *graph)
{
	if (!graph->is_looking_left)
		return (0);
	graph->pa -= 0.01;
	if (graph->pa < 0)
		graph->pa += 2 * PI;
	update_direction_vectors(graph);
	return (1);
}

int	look_right(t_graph *graph)
{
	if (!graph->is_looking_right)
		return (0);
	graph->pa += 0.01;
	if (graph->pa > 2 * PI)
		graph->pa -= 2 * PI;
	update_direction_vectors(graph);
	return (1);
}

int handle_rotation(t_graph *graph)
{
	int	moved;

	moved = 0;
	moved += look_left(graph);
	moved += look_right(graph);
	return (moved > 0);
}
