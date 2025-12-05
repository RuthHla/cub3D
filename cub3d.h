#ifndef CUB3D_H
#define CUB3D_H


# include "minilibx/mlx.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define X_LEFT 65361
# define X_RIGHT 65363

# define IMG_PX 32

# define PI 3.1415926535

typedef struct s_cell
{
	int		x;
	int		y;
	char	type;
}	t_cell;

/* typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*square;
	void	*wall;
}	t_mlx; */

typedef struct s_graph
{
	void	*mlx;
	void	*win;
	void	*square;
	void	*wall;

	size_t	height;
	size_t	width;
	char	**map;

	double		move_speed;
	double		x;
	double		y;
	double		pa;
	double		pdx;
	double		pdy;
	int		grid_x;
	int		grid_y;
	int		player_radius;
	int	is_moving_forward;
	int	is_moving_backward;
	int	is_moving_left;
	int	is_moving_right;
	int	is_looking_right;
	int	is_looking_left;
	double	dirX;
	double	dirY;
}	t_graph;

int	exit_game(t_graph *graph);
char	**create_map_grid(char *map_name);
int	move_loop(t_graph *graph);
int	key_press_hook(int key, t_graph *graph);
int	key_release_hook(int key, t_graph *graph);
void	draw_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int color);

// display.c

void	redraw_display(t_graph *graph);
void	display_minimap(t_graph *graph);

// check_move.c

int check_move(t_graph *graph, double dx, double dy);
int check_move_x(t_graph *graph, double dx);
int check_move_y(t_graph *graph, double dy);

int	handle_movement(t_graph *graph);
int handle_rotation(t_graph *graph);

void	update_direction_vectors(t_graph *graph);

// raycaster.c

void	draw_rays(t_graph *graph);

#endif
