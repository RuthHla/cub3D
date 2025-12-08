#include "cub3d.h"

void	init_image(t_graph *graph)
{
	if (!graph->mlx)
		return ;
	graph->img.img_ptr = mlx_new_image(graph->mlx, WIDTH, HEIGHT);
	if (!graph->img.img_ptr)
		return ;
	graph->img.data_addr = mlx_get_data_addr(
		graph->img.img_ptr,
		&graph->img.bits_per_pixel,
		&graph->img.line_len,
		&graph->img.endian);
}

void ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		// 1. Calcul de l'offset du pixel
		// line_length est la taille en octets d'une ligne entière (WIDTH * bpp / 8)
		// bpp / 8 est le nombre d'octets par pixel (ex: 4 octets pour 32 bits)
		dst = img->data_addr + (y * img->line_len + x * (img->bits_per_pixel / 8));

		// 2. Écriture de la couleur
		// On suppose ici que la couleur est stockée dans un int (4 octets)
		*(unsigned int*)dst = color;
	}
}

int	render_frame(t_graph *graph)
{
	cast_ray(graph, graph->player, graph->player->pa);
	mlx_put_image_to_window(graph->mlx, graph->win, graph->img.img_ptr, 0, 0);
	return (0);
}
