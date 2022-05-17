#include "../includes/wallpaper.h"

static int	ccw(t_point a, t_point b, t_point c)
{
	return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

static int	lines_collide(t_point l1[2], t_point l2[2])
{
	return ccw(l1[0], l2[0], l2[1]) != ccw(l1[1], l2[0], l2[1]) && ccw(l1[0], l1[1], l2[0]) != ccw(l1[0], l1[1], l2[1]);
}

int	pts_are_equal(t_point p1, t_point p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return 1;
	return 0;
}

static int	lines_are_totally_different(t_point l1[2], t_point l2[2])
{
	for (int i = 0; i < 2; i++)
		if (pts_are_equal(l1[0], l2[i]))
			return 0;
	for (int i = 0; i < 2; i++)
		if (pts_are_equal(l1[1], l2[i]))
			return 0;
	return 1;
}

int	triangles_collide(t_triangle t1, t_triangle t2)
{
	t_point	lines[6][2];

	for (int i = 0; i < 3; i++) {
		lines[i][0] = t1.pts[i];
		lines[i][1] = t1.pts[(i + 1) % 3];
	}
	for (int i = 0; i < 3; i++) {
		lines[i + 3][0] = t2.pts[i];
		lines[i + 3][1] = t2.pts[(i + 1) % 3];
	}
	for (int i = 0; i < 6; i++)
		for (int j = i + 1; j < 6; j++)
			if (lines_are_totally_different(lines[i], lines[j]) && lines_collide(lines[i], lines[j]))
				return 1;
	return 0;
}

int	find_same_pt_in_triangles(t_triangle t1, t_triangle t2)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (pts_are_equal(t1.pts[i], t2.pts[j]))
				return i;
	return -1;
}

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

int	triangle_is_out_of_bounds(t_triangle t, int w_min, int w_max, int h_min, int h_max)
{
	for (int i = 0; i < 3; i++)
		if (t.pts[i].x >= w_min && t.pts[i].x <= w_max && t.pts[i].y >= h_min && t.pts[i].y <= h_max)
			return 0;
	return 1;
}

int	triangles_are_equal(t_triangle t1, t_triangle t2)
{
	for (int i = 0; i < 3; i++)
		if (pts_are_equal(t1.pts[0], t2.pts[i]) && pts_are_equal(t1.pts[1], t2.pts[(i + 1) % 3]) && pts_are_equal(t1.pts[2], t2.pts[(i + 2) % 3]))
			return 1;
	if (pts_are_equal(t1.pts[0], t2.pts[0]) && pts_are_equal(t1.pts[1], t2.pts[2]) && pts_are_equal(t1.pts[2], t2.pts[1]))
		return 1;
	if (pts_are_equal(t1.pts[0], t2.pts[2]) && pts_are_equal(t1.pts[1], t2.pts[1]) && pts_are_equal(t1.pts[2], t2.pts[0]))
		return 1;
	if (pts_are_equal(t1.pts[0], t2.pts[1]) && pts_are_equal(t1.pts[1], t2.pts[0]) && pts_are_equal(t1.pts[2], t2.pts[2]))
		return 1;
	return 0;
}

