#include "../includes/wallpaper.h"

static void init(t_god *god)
{
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, WWIDTH, WHEIGHT, "Ubuntu wallpaper");
	god->img = mlx_new_image(god->mlx, WWIDTH, WHEIGHT);
}


static void update(t_god *god)
{
	t_triangle *triangles = malloc(sizeof(t_triangle));

	/// First Triangle
	t_rect rect;
	rect.ul = (t_point){450, 233};
	rect.width = 300;
	rect.height = 200;
	rect.angle = 0;
	triangles[0] = generate_and_draw_triangle(rect, god->img, NULL);
	triangles[0].around = 0;

	for (int i = 1; i < 10; i++)
	{
		int pt_i = fmin(((~triangles[i - 1].around) & 7) / 2, 2);
		t_point base[2] = {triangles[i - 1].pts[pt_i], triangles[i - 1].pts[(pt_i + 1) % 3]};
		rect.ul = base[0];
		t_point	base_v = minus(base[1], base[0]);
		rect.width = norm(base_v);
		rect.height = 200;
		rect.angle = atan2(base_v.y, base_v.x);
		// Orienting the rect
		t_point height_v = {0, rect.height};
		height_v = rotate(height_v, rect.angle);
		if (dot(height_v, minus(triangles[i - 1].pts[(pt_i + 2) % 3], rect.ul)) > 0)
			rect.height *= -1;
		triangles = (t_triangle *)realloc(triangles, (i + 1) * sizeof(t_triangle));
		triangles[i] = generate_and_draw_triangle(rect, god->img, &base);
		triangles[i].around = pow(2, pt_i);
	}
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
