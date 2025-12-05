#include "cub3d.h"

void	draw_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
{
	double  deltaX = (double)abs(x2 - x1);
	double  deltaY = (double)abs(y2 - y1);
	double  steps;
	double  x_inc, y_inc;
	double  x, y;

	if (deltaX > deltaY)
		steps = deltaX;
	else
		steps = deltaY;
	x_inc = deltaX / steps;
	y_inc = deltaY / steps;
	if (x1 > x2)
		x_inc *= -1;
	if (y1 > y2)
		y_inc *= -1;
	x = (double)x1;
	y = (double)y1;
	mlx_pixel_put(mlx, win, (int)x, (int)y, color);
	while (steps-- >= 0)
	{
		x += x_inc;
		y += y_inc;
		mlx_pixel_put(mlx, win, (int)x, (int)y, color);
	}
}
