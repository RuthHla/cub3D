#include "cub3d.h"

float get_ntan(float ra)
{
	if (ra == PI)
		return (0);
	if (ra == 0 || ra == P2)
		return (0);
	return (-tan(ra));
}

void	init_vertical_ray(t_ray *r, t_player *p)
{
	float	nTan;

	r->dof = 0;
	if (r->ra == PI || r->ra == 2 * PI)
	{
		r->dof = 100;
		return ;
	}
	nTan = get_ntan(r->ra);
	if (r->ra > P2 && r->ra < P3)
	{
		r->rx = ((int)(p->px / IMG_PX) * IMG_PX) - 0.0001f;
		r->ry = (p->px - r->rx) * nTan + p->py;

		r->xo = -IMG_PX;
		r->yo = -r->xo * nTan;
	}
	else
	{
		r->rx = ((int)(p->px / IMG_PX) * IMG_PX) + IMG_PX;
		r->ry = (p->px - r->rx) * nTan + p->py;

		r->xo = IMG_PX;
		r->yo = -r->xo * nTan;
	}
}

void hit_v_wall(t_ray *r, t_graph *graph, t_player *p)
{
	while (r->dof < 100)
	{
		r->mx = (int)(r->rx / IMG_PX);
		r->my = (int)(r->ry / IMG_PX);

		if (r->mx < 0 || r->my < 0 || r->mx >= 30 || r->my >= 16)
			break;

		if (graph->map[r->my][r->mx] == '1')
		{
			r->vx = r->rx;
			r->vy = r->ry;
			r->distV = dist(p->px, p->py, r->vx, r->vy);
			r->dof = 100;
		}
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof++;
		}
	}
}
