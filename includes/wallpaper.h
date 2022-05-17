#ifndef WALLPAPER_H
#define WALLPAPER_H

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WWIDTH  1200
#define WHEIGHT 675

#define PI 3.1415926535897932f

#define ESC 65307

typedef struct s_color
{
	int red;
	int green;
	int blue;
}	t_color;

typedef struct s_point
{
	float x;
	float y;
}	t_point;

typedef struct s_rect
{
	int		width;
	int		height;
	t_point	ul;
	float	angle;
}	t_rect;

typedef struct s_triangle
{
	t_point	pts[3];
	int		around;
}	t_triangle;

typedef struct s_god
{
	void	*win;
	void	*mlx;
	void	*img;
	int		coloris;
}	t_god;

// utils.c
int			free_all(t_god *god);
int			key_hook(int keycode, t_god *god);
void		mlx_put_pixel_img(void *img, int x, int y, t_color color);
t_triangle	generate_and_draw_triangle(t_rect rect, void *img, const t_point (*base)[2], t_triangle *triangles, int size, int coloris);
void		draw_pts_rect(t_rect rect, void *img);

// vector.c
t_point		plus(t_point a, t_point b);
t_point		minus(t_point a, t_point b);
t_point		mult(float a, t_point b);
t_point		divv(t_point a, float b);
float		dot(t_point a, t_point b);
t_point 	rotate(t_point v, float angle);
float		norm(t_point v);
void		normalize(t_point *v);

// triangle.c
int		pts_are_equal(t_point p1, t_point p2);
int		bsp(t_point triangle[3], t_point pt);
int		find_same_pt_in_triangles(t_triangle t1, t_triangle t2);
int		triangles_collide(t_triangle t1, t_triangle t2);
int		triangle_is_out_of_bounds(t_triangle t, int w_min, int w_max, int h_min, int h_max);
int		triangles_are_equal(t_triangle t1, t_triangle t2);

#endif // WALLPAPER_H
