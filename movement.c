#include "cub3d.h"

int	move_forward(t_graph *graph)
{
	double	dx;
	double	dy;
	int		moved;

	if (!graph->is_moving_forward)
		return (0);
	dx = graph->dirX * graph->move_speed;
	dy = graph->dirY * graph->move_speed;
	moved = 0;
	if (check_move_x(graph, dx))
	{
		graph->x += dx;
		moved = 1;
	}
	if (check_move_y(graph, dy))
	{
		graph->y += dy;
		moved = 1;
	}
	return (moved);
}

int	move_backward(t_graph *graph)
{
	double	dx;
	double	dy;
	int		moved;

	if (!graph->is_moving_backward)
		return (0);
	dx = -graph->dirX * graph->move_speed;
	dy = -graph->dirY * graph->move_speed;
	moved = 0;
	if (check_move_x(graph, dx))
	{
		graph->x += dx;
		moved = 1;
	}
	if (check_move_y(graph, dy))
	{
		graph->y += dy;
		moved = 1;
	}
	return (moved);
}

int	move_left(t_graph *graph)
{
	double	dx;
	double	dy;
	int		moved;

	if (!graph->is_moving_left)
		return (0);
	dx = graph->dirY * graph->move_speed;
	dy = -graph->dirX * graph->move_speed;
	moved = 0;
	if (check_move_x(graph, dx))
	{
		graph->x += dx;
		moved = 1;
	}
	if (check_move_y(graph, dy))
	{
		graph->y += dy;
		moved = 1;
	}
	return (moved);
}

int	move_right(t_graph *graph)
{
	double	dx;
	double	dy;
	int		moved;

	if (!graph->is_moving_right)
		return (0);
	dx = -graph->dirY * graph->move_speed;
	dy = graph->dirX * graph->move_speed;
	moved = 0;
	if (check_move_x(graph, dx))
	{
		graph->x += dx;
		moved = 1;
	}
	if (check_move_y(graph, dy))
	{
		graph->y += dy;
		moved = 1;
	}
	return (moved);
}

int	handle_movement(t_graph *graph)
{
	int moved;

	moved = 0;
	moved += move_forward(graph);
	moved += move_backward(graph);
	moved += move_left(graph);
	moved += move_right(graph);
	return (moved > 0);
}
