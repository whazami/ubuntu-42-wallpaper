#include "../includes/wallpaper.h"

int	free_all(t_god *god)
{
	mlx_destroy_image(god->mlx, god->img);
	mlx_destroy_window(god->mlx, god->win);
	mlx_destroy_display(god->mlx);
	free(god->mlx);
	exit(0);
}

int	key_hook(int keycode, t_god *god)
{
	if (keycode == ESC)
		free_all(god);
	return (0);
}

void	mlx_put_pixel_img(void *img, int x, int y, t_color color)
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = (int)color.red * pow(16, 4) + (int)color.green * pow(16, 2)
		+ (int)color.blue;
}

static t_point	generate_rand_pt_in_square(t_square s)
{
	t_point vs_flat = {rand() % s.width, rand() % s.height};
	t_point vs = rotate(vs_flat, s.angle);
	t_point res = {s.ul.x + vs.x, s.ul.y + vs.y};
	return res;
}

t_triangle	generate_and_draw_triangle(t_square square, void *img, const t_point (*base)[2])
{
	t_color		rand_red = {255, rand() % 256, 0};	
	t_triangle	triangle;

	if (base == NULL) {
		triangle.pts[0] = generate_rand_pt_in_square(square);
		triangle.pts[1] = generate_rand_pt_in_square(square);
	}
	else {
		triangle.pts[0] = (*base)[0];
		triangle.pts[1] = (*base)[1];
	}
	triangle.pts[2] = generate_rand_pt_in_square(square);
	
	for (int x = 0; x < WWIDTH; x++)
		for (int y = 0; y < WHEIGHT; y++)
			if (bsp(triangle.pts, (t_point){x, y}))
				mlx_put_pixel_img(img, x, y, rand_red);

	return triangle;
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

t_point	minus(t_point a, t_point b)
{
	t_point res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

// Only for debug
void draw_pts_square(t_square square, void *img)
{
	t_color purple = {127, 0, 255};

	t_point tmp;
	for (int i = 0; i < 1000; i++) {
		tmp = generate_rand_pt_in_square(square);
		if (tmp.x >= 0 && tmp.x <= WWIDTH && tmp.y >= 0 && tmp.y <= WHEIGHT)
			mlx_put_pixel_img(img, tmp.x, tmp.y, purple);
	}
}
