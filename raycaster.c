

#include "cub3d.h"

#include <math.h> // Nécessaire pour sin, cos, tan, PI

#define PI 3.1415926535
#define P2 PI / 2
#define P3 3*PI / 2
#define DR 0.0274533

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); // formule de la norme d'un vecteur
}

void	draw_rays(t_graph *graph)
{
	int	r; // Index Ray -> donne le nombre de rayons émis par le joueur
	int mx; // coordonnée x dans la grille
	int my; // coordonnée y dans la grille
//	int mp; // position dans le tableau 1D (inutile dans notre cas?)
	int dof; // depth of field -> empêche le rayon de traverser toute la carte, compte le nombre de murs/cases vérifiées
	float rx; // coordonnée x du point d'impact du rayon dans le canvas
	float ry; // coordonnée y du point d'impact du rayon dans le canvas
	float ra; // angle du rayon
	float xo; // offset utilisé pour passer d'une ligne de la carte à la suivante
	float yo; // offset
	float aTan; // tangente négative inversée utilisé pour calculer les intersections horizontales
	float nTan; // pour calculer les intersections verticales
	float disH;
	float disV;
//	float disT;
	float hx;
	float hy;
	float vx;
	float vy;

	ra = graph->pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 60; r++) // boucle pour lancer les rayons
	{
		disH = 1000000;
		hx = graph->x;
		hy = graph->y;
		// --- CHECK LIGNES HORIZONTALES ---
		dof = 0; // on réinitialise à 0 à chaque boucle (aucun mur ou case vérifiés)
		if (ra == P2 || ra == P3)
			dof = 15;
		else
			aTan = -1 / tan(ra);
		if (ra > PI) // le rayon est orienté vers le bas
		{
			ry = (((int)graph->y / IMG_PX) * IMG_PX) - 0.0001;
			// (int)graph->y / IMG_PX -> donne la coordonnée y dans la grille
			// on remultiplie par IMG_PX pour avoir la bonne coordonnée dans le canvas
			// puis on soustrait pour avoir la liste juste au dessus
			rx = (graph->y - ry) * aTan + graph->x;
			// graph->y - ry donne la hauteur du triangle formé par le joueur et le point (rx, ry) = distance verticale parcourue par le rayon
			// en multipliant par aTan on obtient la distance horizontale parcourue (= côté adjacent du triangle)
			// on ajoute la position de départ du joueur pour la position du triangle et donc la position de rx
			yo = -IMG_PX; // si le rayon descend, l'offset est négatif
			xo = -yo * aTan;
		}
		if (ra < PI) // le rayon est orienté vers le haut
		{
			ry = (((int)graph->y / IMG_PX) * IMG_PX) + IMG_PX; // pour avoir la coordonnée de la ligne horizontale supérieure (+ IMG_PX ou +0.0001?)
			rx = (graph->y - ry) * aTan + graph->x;
			yo = IMG_PX;
			xo = -yo * aTan;
		}
		while (dof < 15)
		{
			mx = (int)rx / IMG_PX; // coordonnées du rayon dans la grille
			my = (int)ry / IMG_PX;
			if (mx < 0 || my < 0 || mx >= 30 || my >= 16)
				break;
			if (mx >= 0 && my >= 0 && mx < 30 && my < 16 && graph->map[my][mx] == '1')
			{
				hx = rx;
				hy = ry;
				disH = dist(graph->x, graph->y, hx, hy);
				dof = 15; // on arrête la boucle (break plutôt?)
			}
			else
			{
				// l'angle ra ne change pas donc il y a juste a ajouter l'offset pour vérifier la ligne suivante
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		// --- CHECK LIGNES VERTICALES ---
		disV = 1000000;
		vx = graph->x;
		vy = graph->y;
		dof = 0;
		nTan = -tan(ra);
		if (ra > P2 && ra < P3) // le rayon est orienté vers la droite
		{
			rx = (((int)graph->x / IMG_PX) * IMG_PX) - 0.0001;
			ry = (graph->x - rx) * nTan + graph->y;
			xo = -IMG_PX; // si le rayon descend, l'offset est négatif
			yo = -xo * nTan;
		}
		else if (ra < P2 || ra > P3) // le rayon est orienté vers la gauche
		{
			rx = (((int)graph->x / IMG_PX) * IMG_PX) + IMG_PX; // pour avoir la coordonnée de la ligne horizontale supérieure (+ IMG_PX ou +0.0001?)
			ry = (graph->x - rx) * nTan + graph->y;
			xo = IMG_PX;
			yo = -xo * nTan;
		}
		else if (ra == P2 || ra == P3) // le rayon est orienté vers la gauche ou la droite (parallèle aux abscisses), évite les divisions par 0
		{
			rx = graph->x;
			ry = graph->y;
			dof = 15;
		}
		else if (ra == 0 || ra == PI) // le rayon est orienté vers la gauche ou la droite (parallèle aux abscisses), évite les divisions par 0
		{
			rx = graph->x;
			ry = graph->y;
			dof = 15;
		}
		while (dof < 15)
		{
			mx = (int)rx / IMG_PX; // coordonnées du rayon dans la grille
			my = (int)ry / IMG_PX;
			if (mx < 0 || my < 0 || mx >= 30 || my >= 16)
				break;
			if (mx >= 0 && my >= 0 && mx < 30 && my < 16 && graph->map[my][mx] == '1')
			{
				vx = rx;
				vy = ry;
				disV = dist(graph->x, graph->y, vx, vy);
				dof = 15; // on arrête la boucle (break plutôt?)
			}
			else
			{
				// l'angle ra ne change pas donc il y a juste a ajouter l'offset pour vérifier la ligne suivante
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
//			disT = disH;
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
//			disT = disV;
		}
		draw_line(graph->mlx, graph->win, graph->x, graph->y, rx, ry, 0xFF0000);

		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}
