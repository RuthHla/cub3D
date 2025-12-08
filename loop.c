#include "cub3d.h"

void	update_grid_position(t_player *player)
{
	player->grid_x = (int)(player->px / IMG_PX);
	player->grid_y = (int)(player->py / IMG_PX);
}

int	key_press_hook(int key, t_graph *graph)
{
	t_player	*player;

	player = graph->player;
	if (key == W_KEY)
		player->is_moving_forward = 1;
	if (key == S_KEY)
		player->is_moving_backward = 1;
	if (key == A_KEY)
		player->is_moving_left = 1;
	if (key == D_KEY)
		player->is_moving_right = 1;
	if (key == X_RIGHT)
		player->is_looking_right = 1;
	if (key == X_LEFT)
		player->is_looking_left = 1;
	return (0);
}

int	key_release_hook(int key, t_graph *graph)
{
	t_player	*player;

	player = graph->player;
	if (key == W_KEY)
		player->is_moving_forward = 0;
	if (key == S_KEY)
		player->is_moving_backward = 0;
	if (key == A_KEY)
		player->is_moving_left = 0;
	if (key == D_KEY)
		player->is_moving_right = 0;
	if (key == X_RIGHT)
		player->is_looking_right = 0;
	if (key == X_LEFT)
		player->is_looking_left = 0;
	return (0);
}

int	move_loop(t_graph *graph)
{
	int	moved;
	int	rotated;
	update_grid_position(graph->player);
	moved = handle_movement(graph, graph->player);
	rotated = handle_rotation(graph->player);
	if (moved || rotated)
		render_frame(graph);
	return (0);
}


