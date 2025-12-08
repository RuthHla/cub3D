#include "cub3d.h"

void	update_direction_vectors(t_player *player)
{
	player->dirX = cos(player->pa);
	player->dirY = sin(player->pa);
}

int	look_left(t_player *player)
{
	if (!player->is_looking_left)
		return (0);
	player->pa -= player->rotation_speed;
	if (player->pa < 0)
		player->pa += 2 * PI;
	update_direction_vectors(player);
	return (1);
}

int	look_right(t_player *player)
{
	if (!player->is_looking_right)
		return (0);
	player->pa += player->rotation_speed;
	if (player->pa > 2 * PI)
		player->pa -= 2 * PI;
	update_direction_vectors(player);
	return (1);
}

int handle_rotation(t_player *player)
{
	int	moved;

	moved = 0;
	moved += look_left(player);
	moved += look_right(player);
	return (moved > 0);
}
