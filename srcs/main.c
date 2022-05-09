#include "../includes/wallpaper.h"

static void init(t_god *god)
{
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, WWIDTH, WHEIGHT, "Ubuntu wallpaper");
	god->img = mlx_new_image(god->mlx, WWIDTH, WHEIGHT);
}


static void update(t_god *god)
{
	t_square square;
	square.ul = (t_point){450, 233};
	square.width = 300;
	square.height = 200;
	square.angle = 0;

	t_triangle t = generate_and_draw_triangle(square, god->img, NULL);
	t_point base[2] = {t.pts[0], t.pts[1]};
	square.ul = base[0];
	t_point	base_v = minus(base[1], base[0]);
	square.width = norm(base_v);
	square.height = 200;
	square.angle = atan2(base_v.y, base_v.x);
	draw_pts_square(square, god->img);
	generate_and_draw_triangle(square, god->img, &base);
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
