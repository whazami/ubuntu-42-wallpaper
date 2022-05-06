#include "../includes/wallpaper.h"

static void init(t_god *god)
{
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, WWIDTH, WHEIGHT, "Ubuntu wallpaper");
	god->img = mlx_new_image(god->mlx, WWIDTH, WHEIGHT);
}

static void update(t_god *god)
{
	t_color purple = {127, 0, 255};
	t_color cyan = {0, 255, 255};

	for (int x = 0; x < WWIDTH / 2; x++)
		for (int y = 0; y < WHEIGHT / 2; y++)
			mlx_put_pixel_img(god->img, x, y, purple);

	t_point triangle[3] = {(t_point){800, 200}, (t_point){1000, 150}, (t_point){950, 350}};
	draw_triangle(god->img, triangle, cyan);
}

int main(void)
{
	t_god	god;

	init(&god);
	update(&god);
	mlx_put_image_to_window(god.mlx, god.win, god.img, 0, 0);
	mlx_key_hook(god.win, key_hook, &god);
	mlx_hook(god.win, 17, 0L, free_all, &god);
	mlx_loop(god.mlx);
	return (0);
}
