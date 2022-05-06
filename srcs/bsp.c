#include "../includes/wallpaper.h"

static float triangle_area(t_point triangle[3])
{
	t_point a = triangle[0];
	t_point b = triangle[1];
	t_point c = triangle[2];
	float area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

	area /= 2;
	if (area < 0)
		area = -area;

	return area;
}

int bsp(t_point triangle[3], t_point pt)
{
	float areas[3];
	float t_area;

	t_area = triangle_area(triangle);
	areas[0] = triangle_area((t_point[3]){pt, triangle[0], triangle[1]});
	areas[1] = triangle_area((t_point[3]){pt, triangle[1], triangle[2]});
	areas[2] = triangle_area((t_point[3]){pt, triangle[0], triangle[2]});
	
	float sum = 0;
	for (int i = 0; i < 3; i++) {
		if (areas[i] == 0)
			return 0;
		sum += areas[i];
	}
	if (sum == t_area)
		return 1;
	return 0;
}
