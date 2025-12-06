#include "cub.h"

#define TILE 128      // taille des tiles
#define mapX 8        // dimension de la map en x
#define mapY 8        // dimension de la map en y

#define COLOR_WALL   0x00FFFFFF
#define COLOR_FLOOR  0x00000000
#define COLOR_PLAYER 0x0000FF00

// FOV du joueur (en radians)
#define FOV       (107.0f * M_PI / 180.0f)  // 107°
#define NUM_RAYS  60

// Taille de fenêtre (pour l'instant == taille de la map en pixels)
#define WIDTH  (mapX * TILE)
#define HEIGHT (mapY * TILE)

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

void	*mlx;
void	*win;
t_img	img;

// textures globales
t_tex	g_wall_tex;

// position / orientation du joueur
float	pdx = 0; // vecteur (donc sens)
float	pdy = 0;
float	px  = TILE * 2; // position du player
float	py  = TILE * 2;
float	pa  = 0; // angle de vue

// flags touches enfoncées
int		key_w = 0;
int		key_s = 0;
int		key_a = 0;
int		key_d = 0;

// map 8x8 : 1 = mur, 0 = sol
int	map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

/*==========================================================
  UTILS PIXELS / MAP
  ==========================================================*/

void	img_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	unsigned int *pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	pixel = (unsigned int *)(img->addr
			+ y * img->line_len + x * (img->bpp / 8));
	*pixel = color;
}

// renvoie 1 si la position (x, y) est du sol (= walkable), 0 sinon
int	is_floor_at(float x, float y)
{
	int	cx;
	int	cy;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	cx = (int)(x / TILE);
	cy = (int)(y / TILE);
	return (map[cy * mapX + cx] == 0);
}

void	draw_square(int sx, int sy, int size, unsigned int color)
{
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			img_pixel_put(&img, sx + i, sy + j, color);
}

void	draw_square_outline(int sx, int sy, int size, unsigned int color)
{
	for (int i = 0; i < size; i++)
	{
		img_pixel_put(&img, sx + i, sy, color);
		img_pixel_put(&img, sx + i, sy + size - 1, color);
		img_pixel_put(&img, sx, sy + i, color);
		img_pixel_put(&img, sx + size - 1, sy + i, color);
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
	int size = TILE / 2;

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

/*==========================================================
  RAYCAST
  ==========================================================*/

// renvoie la distance jusqu'au mur dans la direction `angle`
// et écrit le point d'impact dans *hit_x / *hit_y
float	cast_ray(float angle, float *hit_x, float *hit_y)
{
	float dir_x = cosf(angle);
	float dir_y = sinf(angle);
	float t = 0.0f;

	while (1)
	{
		float fx = px + dir_x * t;
		float fy = py + dir_y * t;

		if (fx < 0 || fx >= WIDTH || fy < 0 || fy >= HEIGHT)
			break;
		if (!is_floor_at(fx, fy))
			break;
		t += 1.0f;
	}
	if (hit_x)
		*hit_x = px + dir_x * t;
	if (hit_y)
		*hit_y = py + dir_y * t;
	return (t);
}

/*==========================================================
  TEXTURES
  ==========================================================*/

unsigned int	tex_get_pixel(t_tex *tex, int x, int y)
{
	char	*px;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	px = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)px);
}

/*==========================================================
  3D VIEW
  ==========================================================*/

void	draw_vertical_line(int x, int y_top, int y_bottom, unsigned int color)
{
	if (x < 0 || x >= WIDTH)
		return;
	if (y_top < 0)
		y_top = 0;
	if (y_bottom >= HEIGHT)
		y_bottom = HEIGHT - 1;
	for (int y = y_top; y <= y_bottom; y++)
		img_pixel_put(&img, x, y, color);
}

void	draw_3d_view(void)
{
	float dir_x = cosf(pa);
	float dir_y = sinf(pa);

	float plane_size = tanf(FOV / 2.0f);
	float plane_x = -dir_y * plane_size; // segment gauche de leventail
	float plane_y =  dir_x * plane_size; // segment droit de  leventail

	float dist_proj_plane = (WIDTH / 2.0f) / tanf(FOV / 2.0f);

	for (int col = 0; col < WIDTH; col++)
	{
		float camera_x = 2.0f * col / (float)WIDTH - 1.0f;

		float ray_dir_x = dir_x + plane_x * camera_x;
		float ray_dir_y = dir_y + plane_y * camera_x;

		float ray_angle = atan2f(ray_dir_y, ray_dir_x);
		ray_angle = normalize_angle(ray_angle);

		float hit_x;
		float hit_y;
		float raw_dist = cast_ray(ray_angle, &hit_x, &hit_y);

		float corrected_dist = raw_dist * cosf(ray_angle - pa);
		if (corrected_dist < 0.001f)
			corrected_dist = 0.001f;

		float wall_height_f = (TILE * dist_proj_plane) / corrected_dist;
		int   wall_height = (int)wall_height_f;

		int wall_top = HEIGHT / 2 - wall_height / 2;
		int wall_bottom = HEIGHT / 2 + wall_height / 2;

		// --- ciel (uni) ---
		draw_vertical_line(col, 0, wall_top - 1, 0x00000055);

		// --- mur texturé ---
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= HEIGHT)
			wall_bottom = HEIGHT - 1;

		// position dans la tuile touchée
		float wall_x = fmodf(hit_x, TILE);
		// version simple : on projette sur X (ça suffira pour commencer)
		int tex_x = (int)(wall_x / TILE * g_wall_tex.width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= g_wall_tex.width)
			tex_x = g_wall_tex.width - 1;

		for (int y = wall_top; y <= wall_bottom; y++)
		{
			float rel = (float)(y - wall_top) / (float)(wall_bottom - wall_top);
			int tex_y = (int)(rel * g_wall_tex.height);
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= g_wall_tex.height)
				tex_y = g_wall_tex.height - 1;
			unsigned int color = tex_get_pixel(&g_wall_tex, tex_x, tex_y);
			img_pixel_put(&img, col, y, color);
		}

		// --- sol (uni pour l'instant) ---
		draw_vertical_line(col, wall_bottom + 1, HEIGHT - 1, 0x00333333);
	}
}

/*==========================================================
  RENDER
  ==========================================================*/

void	render(void)
{
	draw_square(0, 0, WIDTH, COLOR_FLOOR);
	draw_3d_view();
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
}

/*==========================================================
  MOUVEMENT / CLAVIER
  ==========================================================*/

void	update_direction(void)
{
	float speed = TILE / 64.0f;

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

	if (key_a)
	{
		pa -= 0.05f;
		if (pa < 0)
			pa += 2 * M_PI;
		update_direction();
	}
	if (key_d)
	{
		pa += 0.05f;
		if (pa > 2 * M_PI)
			pa -= 2 * M_PI;
		update_direction();
	}
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

/*==========================================================
  TEXTURE LOADING + MAIN
  ==========================================================*/

void	load_texture(t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		write(2, "Error\nFailed to load texture\n", 29);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nprogram expected -> ./cub3D path/map.cub3d\n");
		return 1;
	}
	if (!check_arg(av[1]))
		return 1;

	t_data *data = NULL;
	if(!save_map(av[1], data))
		return 1;

	//init_data();
	
	//init_map(char **map)
	//check_map(t_data *data)

	//fichier vide + check texture
	// if(!check_map(av[1], ))

	mlx = mlx_init();
	if (!mlx)
		return (1);

	load_texture(&g_wall_tex, "./sprites/wall_blue.xpm");

	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Cub3D Mini View");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	update_direction();
	render();

	// boucle infinie :
	//   lire l’état des touches
	//   mettre à jour position / angle
	//   recalculer tout le raycasting
	//   redessiner l’image complète (mur + sol + textures)
	mlx_hook(win, 2, 1L << 0, key_press, NULL);
	mlx_hook(win, 3, 1L << 1, key_release, NULL);
	mlx_loop_hook(mlx, update, NULL);
	mlx_loop(mlx);
	return (0);
}
