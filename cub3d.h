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
# define P2 (PI / 2)
# define P3 (3*PI / 2)

# define DR 0.0174533 // 1 degré en radians

# define WIDTH (30 * 32)
# define HEIGHT (16 * 32)

# define FOV (60.0f * DR)

typedef struct s_player
{
	double	px;
	double	py;
	int		grid_x;
	int		grid_y;
	double	pa;
	double	dirX;
	double	dirY;
	double	move_speed;
	double	rotation_speed;
	int		radius;
	int	is_moving_forward;
	int	is_moving_backward;
	int	is_moving_left;
	int	is_moving_right;
	int	is_looking_right;
	int	is_looking_left;
}	t_player;

typedef struct s_ray
{
	float	dof;
	float	ra;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	int		mx;
	int		my;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	distH;
	float	distV;
}	t_ray;

/*
Structure pour dessiner tous les pixels hors écran puis les afficher
d'un seul coup

-*img_ptr : pointeur vers l'image, pour l'afficher ou la détruire
-*data_addr : pointeur vers le buffer de pixels où sont stockées toutes
les couleurs de tous les pixels de l'image affichée
-bits_per_pixel : bits utilisés pour représenter la couleur des pixels
-line_len : nombre d'octets utilisés une ligne horizontale complète
-endian : indique l'ordre dans lequel les octets sont stockés pour un
même pixel
 */
typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;


typedef struct s_graph
{
	void	*mlx;
	void	*win;
	void	*square;
	void	*wall;
	char	**map;
	t_player	*player;
	t_img		img;
	size_t	height;
	size_t	width;
}	t_graph;

int	exit_game(t_graph *graph);
char	**create_map_grid(char *map_name);
int	move_loop(t_graph *graph);
int	key_press_hook(int key, t_graph *graph);
int	key_release_hook(int key, t_graph *graph);
void	draw_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int color);

// display.c

void	redraw_display(t_graph *graph, t_player *player);
void	display_minimap(t_graph *graph);

// check_move.c

int check_move(t_graph *graph, double dx, double dy);
int check_move_x(t_graph *graph, t_player *player, double dx);
int check_move_y(t_graph *graph, t_player *player, double dy);

int	handle_movement(t_graph *graph, t_player *player);
int handle_rotation(t_player *player);

void	update_direction_vectors(t_player *player);

void	cast_test_horizontal_ray(t_graph *graph, t_player *player, float ra);

void cast_ray(t_graph *graph, t_player *player, float ra);

// raycaster.c

void	draw_rays(t_graph *graph);
void	draw_rays_minimap(t_graph *graph);

void	init_horizontal_ray(t_ray *ray, t_player *player);
void	hit_h_wall(t_ray *ray, t_graph *graph, t_player *player);
void	init_vertical_ray(t_ray *ray, t_player *player);
void	hit_v_wall(t_ray *ray, t_graph *graph, t_player *player);

float	normalise_angle(float angle);
float	dist(float ax, float ay, float bx, float by);

// render
void	ft_pixel_put(t_img *img, int x, int y, int color);

void	init_image(t_graph *graph);
int		render_frame(t_graph *graph);
#endif
