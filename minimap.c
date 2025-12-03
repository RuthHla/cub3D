#include "../minilibx_macos/mlx.h"
#include <stdlib.h>
#include <math.h>

#define TILE 64
#define mapX 8 
#define mapY 8 

#define COLOR_WALL 0x00FFFFFF
#define COLOR_FLOOR 0x00000000
#define COLOR_PLAYER 0x0000FF00

#define FOV       (107.0f * M_PI / 180.0f)  // 107° en radians
#define NUM_RAYS  60                        // exemple avec 60 rayons

typedef struct s_img
{
	void	*img; // contient l'image'
	char	*addr; // pointeur sur le début de l’image en mémoire (pixel en haut à gauche).
	int		bpp; // bits per pixel → nombre de bits par pixel (souvent 32, donc 4 octets).
	int		line_len; // le nombre d’octets pour une ligne complète de l’image.
	int		endian;
}			t_img;

void		*mlx;
void		*win;
t_img		img;

float		pdx = 0; // direction deplacement
float		pdy = 0;
float		px = TILE * 2; // position player
float		py = TILE * 2;

float 		pa = 0; // orientation/regard du joueur

// touches enfoncées
int			key_w = 0;
int			key_s = 0;
int			key_a = 0;
int			key_d = 0;


int			map[] = 
{1, 1, 1, 1, 1, 1, 1, 1, 
 1, 0, 0, 0, 0, 0, 0, 1,
 1, 0, 0, 1, 1, 0, 0, 1, 
 1, 0, 0, 0, 0, 0, 0, 1, 
 1, 0, 1, 1, 1, 1, 0, 1, 
 1, 0, 0, 0, 0, 0, 0, 1, 
 1, 0, 0, 0, 0, 0, 0, 1, 
 1, 1, 1, 1, 1, 1, 1, 1};

// Width et Height basés sur la map :
#define WIDTH (mapX * TILE)
#define HEIGHT (mapY * TILE)

void	img_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	unsigned int *pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;

	pixel = (unsigned int *)(img->addr + y * img->line_len + x * (img->bpp / 8));
	*pixel = color;
}

int	is_floor_at(float x, float y)
{
	// 1) sécurité sur les pixels
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0); // hors de l'écran => pas walkable

	// 2) conversion pixels -> indices de case
	int cx = (int)(x / TILE);
	int cy = (int)(y / TILE);

	return (map[cy * mapX + cx] == 0);
}

void	draw_square(int px, int py, int size, unsigned int color)
{
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			img_pixel_put(&img, px + i, py + j, color);
}

void	draw_square_outline(int px, int py, int size, unsigned int color)
{
	for (int i = 0; i < size; i++)
	{
		// haut et bas
		img_pixel_put(&img, px + i, px, color);
		img_pixel_put(&img, px + i, py + size - 1, color);

		// gauche et droite
		img_pixel_put(&img, px, py + i, color);
		img_pixel_put(&img, px + size - 1, py + i, color);
	}
}


void	draw_map(void)
{
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			int screen_x = x * TILE;
			int screen_y = y * TILE;

			if (map[y * mapX + x] == 1)
				draw_square(screen_x, screen_y, TILE, COLOR_WALL);
			else
				draw_square(screen_x, screen_y, TILE, COLOR_FLOOR);

			draw_square_outline(screen_x, screen_y, TILE, 0x00333333);
		}
	}
}

void	draw_player(void)
{
	int	size;

	size = TILE / 2;
	draw_square(px - size / 2, py - size / 2, size, COLOR_PLAYER);
}

// remet l'angle dans [0, 2*PI[
static float	normalize_angle(float a)
{
	while (a < 0)
		a += 2 * M_PI;
	while (a >= 2 * M_PI)
		a -= 2 * M_PI;
	return (a);
}

// dessine UN rayon dans la direction `angle`
void	draw_single_ray(float angle)
{
	float	dir_x;
	float	dir_y;
	float	t;

	dir_x = cosf(angle);
	dir_y = sinf(angle);

	t = 0.0f;
	while (1)
	{
		float fx = px + dir_x * t;
		float fy = py + dir_y * t;

		if (fx < 0 || fx >= WIDTH || fy < 0 || fy >= HEIGHT)
			break;

		if (!is_floor_at(fx, fy))
			break;

		img_pixel_put(&img, (int)fx, (int)fy, 0x00FF0000);

		t += 1.0f;
	}
}

void	draw_rays(void)
{
	float start_angle;
	float angle_step;
	int   i;

	// on veut des rayons entre pa - FOV/2 et pa + FOV/2
	start_angle = pa - (FOV / 2.0f);
	angle_step = FOV / (NUM_RAYS - 1);

	i = 0;
	while (i < NUM_RAYS)
	{
		float ray_angle = start_angle + i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		draw_single_ray(ray_angle);
		i++;
	}
}

void	render(void)
{
	draw_square(0, 0, WIDTH, COLOR_FLOOR);
	draw_map();
	draw_player();
	draw_rays();
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
}


void update_direction()
{
	float speed;

	speed = TILE / 64.0f; // distance parcourue par pas de W/S
	pdx = cosf(pa) * speed;
	pdy = sinf(pa) * speed;
}

int	key_press(int key, void *param)
{
	(void)param;
	if (key == 53) // ESC
		exit(0);
	if (key == 13)    // W
		key_w = 1;
	if (key == 1)     // S
		key_s = 1;
	if (key == 0)     // A
		key_a = 1;
	if (key == 2)     // D
		key_d = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	(void)param;
	if (key == 13)    // W
		key_w = 0;
	if (key == 1)     // S
		key_s = 0;
	if (key == 0)     // A
		key_a = 0;
	if (key == 2)     // D
		key_d = 0;
	return (0);
}

int	update(void *param)
{
	float	new_px;
	float	new_py;

	(void)param;

	// rotation gauche (A)
	if (key_a)
	{
		pa -= 0.05f;
		if (pa < 0)
			pa += 2 * M_PI;
		update_direction();
	}

	// rotation droite (D)
	if (key_d)
	{
		pa += 0.05f;
		if (pa > 2 * M_PI)
			pa -= 2 * M_PI;
		update_direction();
	}

	// avancer (W)
	if (key_w)
	{
		new_px = px + pdx;
		new_py = py + pdy;
		if (is_floor_at(new_px, new_py))
		{
			px = new_px;
			py = new_py;
		}
	}

	// reculer (S)
	if (key_s)
	{
		new_px = px - pdx;
		new_py = py - pdy;
		if (is_floor_at(new_px, new_py))
		{
			px = new_px;
			py = new_py;
		}
	}

	render();
	return (0);
}


int	main(void)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Minimap Buffer");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	render();
	mlx_hook(win, 2, 1L << 0, key_press, NULL);   // KeyPress
	mlx_hook(win, 3, 1L << 1, key_release, NULL); // KeyRelease
	mlx_loop_hook(mlx, update, NULL);             // appelée en continu
	mlx_loop(mlx);
	return (0);
}

	// vision player ->
	// vers la droite : pa = 0 ou pa = 2 * M_PI; mais 0 suffit
	// ou vers le bas :    pa = M_PI / 2;
	// ou vers la gauche : pa = M_PI;
	// ou vers le haut :   pa = 3 * M_PI / 2;