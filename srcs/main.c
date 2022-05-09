#include "../includes/wallpaper.h"

static void init(t_god *god)
{
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, WWIDTH, WHEIGHT, "Ubuntu wallpaper");
	god->img = mlx_new_image(god->mlx, WWIDTH, WHEIGHT);
}

static void update(t_god *god)
{
	t_color rand_red = {255, rand() % 256, 0};
	
	t_square square;
	square.width = 150;
	square.height = 100;
	square.ul = (t_point){80, 30};
	square.angle = PI / 4;
	t_point tmp;
	for (int i = 0; i < 10000; i++) {
		tmp = generate_rand_pt_in_square(square);
		if (tmp.x >= 0 && tmp.x <= WWIDTH && tmp.y >= 0 && tmp.y <= WHEIGHT)
			mlx_put_pixel_img(god->img, tmp.x, tmp.y, rand_red);
	}

	square.ul = (t_point){450, 233};
	square.width = 300;
	square.height = 200;
	square.angle = 0;
	t_point triangle[3];
	triangle[0] = generate_rand_pt_in_square(square);
	triangle[1] = generate_rand_pt_in_square(square);
	triangle[2] = generate_rand_pt_in_square(square);
	draw_triangle(god->img, triangle, rand_red);
}

int main(void)
{
	t_god	god;

	srand(time(NULL));
	init(&god);
	update(&god);
	mlx_put_image_to_window(god.mlx, god.win, god.img, 0, 0);
	mlx_key_hook(god.win, key_hook, &god);
	mlx_hook(god.win, 17, 0L, free_all, &god);
	mlx_loop(god.mlx);
	return (0);
}
