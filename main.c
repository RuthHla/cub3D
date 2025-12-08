#include "cub3d.h"

int main()
{
	t_graph	*graph;
	t_player *player;
	int		size;

	size = 32;
	graph = malloc(sizeof(t_graph));
	if (!graph)
		return (1);
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, 30 * IMG_PX, 16 * IMG_PX, "CUB3D");
	graph->square = mlx_xpm_file_to_image(graph->mlx, "assets/square.xpm", &size, &size);
	init_image(graph);
	player = malloc(sizeof(t_player));
	if (!player)
		return (1);
	graph->player = player;
	player->radius = 10;
	player->rotation_speed = 0.01;
	player->px = 2 * IMG_PX + player->radius;
	player->py = 2 * IMG_PX + player->radius;
	graph->wall = mlx_xpm_file_to_image(graph->mlx, "assets/walls.xpm", &size, &size);
	graph->map = create_map_grid("map.cub");
	player->pa = PI / 3; // attention problème de boucle infinie avec le raycasting
	player->move_speed = 0.8;
	mlx_hook(graph->win, 2, 1L<<0, key_press_hook, graph);
	mlx_hook(graph->win, 3, 1L<<1, key_release_hook, graph);
	mlx_loop_hook(graph->mlx, move_loop, graph);
	mlx_hook(graph->win, 17, 0, exit_game, graph);
	update_direction_vectors(player);
	render_frame(graph);
//	redraw_display(graph, player);
	mlx_loop(graph->mlx);

	return 0;
}
