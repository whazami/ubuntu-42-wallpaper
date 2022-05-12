#include "../includes/wallpaper.h"

t_point	plus(t_point a, t_point b)
{
	t_point res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

t_point	minus(t_point a, t_point b)
{
	t_point res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

t_point	mult(float a, t_point b)
{
	t_point res;

	res.x = a + b.x;
	res.y = a + b.y;
	return res;
}

t_point	divv(t_point a, float b)
{
	t_point res;

	res.x = a.x / b;
	res.y = a.y / b;
	return res;
}

float	dot(t_point a, t_point b)
{
	float res;

	res = a.x * b.x + a.y * b.y;
	return res;
}

t_point rotate(t_point v, float angle)
{
	t_point res;

	res.x = cos(angle) * v.x - sin(angle) * v.y;
	res.y = sin(angle) * v.x + cos(angle) * v.y;
	return res;
}

float	norm(t_point v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void	normalize(t_point *v)
{
	float	n;

	n = norm(*v);
	v->x /= n;
	v->y /= n;
}
