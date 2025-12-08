#include "cub3d.h"

float	get_atan(float ra)
{
	if (ra == P2 || ra == P3)
	{
		return (0);
	}
	return (-1.0f / tan(ra));
}

void	init_horizontal_ray(t_ray *r, t_player *p)
{
	float	aTan;

	r->dof = 0;
	if (r->ra == P2 || r->ra == P3)
	{
		r->dof = 100;
		return ;
	}
	aTan = get_atan(r->ra);
	if (r->ra > PI)
	{
		r->ry = ((int)(p->py / IMG_PX) * IMG_PX) - 0.0001f;
		r->rx = (p->py - r->ry) * aTan + p->px;
		r->yo = -IMG_PX;
		r->xo = -r->yo * aTan;
	}
	else
	{
		r->ry = ((int)(p->py / IMG_PX) * IMG_PX) + IMG_PX;
		r->rx = (p->py - r->ry) * aTan + p->px;
		r->yo =  IMG_PX;
		r->xo = -r->yo * aTan;
	}
}

void	hit_h_wall(t_ray *r, t_graph *graph, t_player *p)
{
	while (r->dof < 100)
	{
		r->mx = (int)r->rx / IMG_PX; // coordonnées du rayon dans la grille
		r->my = (int)r->ry / IMG_PX;
		if (r->mx < 0 || r->my < 0 || r->mx >= 30 || r->my >= 16)
			break;
		if (r->mx >= 0 && r->my >= 0 && r->mx < 30 && r->my < 16 && graph->map[r->my][r->mx] == '1')
		{
			r->hx = r->rx;
			r->hy = r->ry;
			r->distH = dist(p->px, p->py, r->hx, r->hy);
			r->dof = 100; // on arrête la boucle (break plutôt?)
		}
		else
		{
			// l'angle ra ne change pas donc il y a juste a ajouter l'offset pour vérifier la ligne suivante
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof++;
		}
	}
}
