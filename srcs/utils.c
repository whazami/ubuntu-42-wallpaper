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

void	draw_triangle(void *img, t_point triangle[3], t_color color)
{
	for (int x = 0; x < WWIDTH; x++)
		for (int y = 0; y < WHEIGHT; y++)
			if (bsp(triangle, (t_point){x, y}))
				mlx_put_pixel_img(img, x, y, color);
}
