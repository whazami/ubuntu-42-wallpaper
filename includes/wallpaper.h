#ifndef WALLPAPER_H
#define WALLPAPER_H

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WWIDTH  1200
#define WHEIGHT 675

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

typedef struct s_god
{
	void	*win;
	void	*mlx;
	void	*img;
}	t_god;

int		free_all(t_god *god);
int		key_hook(int keycode, t_god *god);
void	mlx_put_pixel_img(void *img, int x, int y, t_color color);
void	draw_triangle(void *img, t_point triangle[3], t_color color);
int		bsp(t_point triangle[3], t_point pt);

#endif // WALLPAPER_H
