#include "cub3d.h"

void	display_minimap(t_graph *graph)
{
	int	x;
	int	y;

	y = 0;
	while (graph->map[y])
	{
		x = 0;
		while (graph->map[y][x])
		{
			if (graph->map[y][x] == '1')
				mlx_put_image_to_window(graph->mlx, graph->win, graph->wall, x * IMG_PX, y * IMG_PX);
			x++;
		}
		y++;
	}
}
void	redraw_display(t_graph *graph, t_player *player)
{
		mlx_clear_window(graph->mlx, graph->win);
//		display_minimap(graph);
//		mlx_put_image_to_window(graph->mlx, graph->win, graph->square, player->px - player->radius, player->py - player->radius);
		cast_ray(graph, player, player->pa);
//		draw_line(graph->mlx, graph->win, graph->x, graph->y, graph->x + graph->pdx * 50, graph->y + graph->pdy * 50, 0xFF0000);
//		draw_rays_minimap(graph);
}
