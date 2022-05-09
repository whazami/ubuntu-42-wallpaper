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

typedef struct s_square
{
	int		width;
	int		height;
	t_point	ul;
	float	angle;
}	t_square;

typedef struct s_god
{
	void	*win;
	void	*mlx;
	void	*img;
}	t_god;

// utils.c
int		free_all(t_god *god);
int		key_hook(int keycode, t_god *god);
void	mlx_put_pixel_img(void *img, int x, int y, t_color color);
void	draw_triangle(void *img, t_point triangle[3], t_color color);
t_point rotate(t_point v, float angle);
t_point	generate_rand_pt_in_square(t_square s);

// bsp.c
int		bsp(t_point triangle[3], t_point pt);

#endif // WALLPAPER_H
