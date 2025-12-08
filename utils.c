#include "cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); // formule de la norme d'un vecteur
}

float	normalise_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return angle;
}
