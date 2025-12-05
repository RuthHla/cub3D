#include "cub3d.h"

int	exit_game(t_graph *graph)
{
	mlx_destroy_window(graph->mlx, graph->win);
	free(graph);
	exit(0);
}
