#include "cub3d.h"

int	move_forward(t_graph *graph, t_player *player)
{
	double	dx;
	double	dy;
	int		moved;

	if (!player->is_moving_forward)
		return (0);
	dx = player->dirX * player->move_speed;
	dy = player->dirY * player->move_speed;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

int	move_backward(t_graph *graph, t_player *player)
{
	double	dx;
	double	dy;
	int		moved;

	if (!player->is_moving_backward)
		return (0);
	dx = -player->dirX * player->move_speed;
	dy = -player->dirY * player->move_speed;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

int	move_left(t_graph *graph, t_player *player)
{
	double	dx;
	double	dy;
	int		moved;

	if (!player->is_moving_left)
		return (0);
	dx = player->dirY * player->move_speed;
	dy = -player->dirX * player->move_speed;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

int	move_right(t_graph *graph, t_player *player)
{
	double	dx;
	double	dy;
	int		moved;

	if (!player->is_moving_right)
		return (0);
	dx = -player->dirY * player->move_speed;
	dy = player->dirX * player->move_speed;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

int	handle_movement(t_graph *graph, t_player *player)
{
	int moved;

	moved = 0;
	moved += move_forward(graph, player);
	moved += move_backward(graph, player);
	moved += move_left(graph, player);
	moved += move_right(graph, player);
	return (moved > 0);
}
