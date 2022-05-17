#include "../includes/wallpaper.h"
#include <sys/time.h>

#define RECT_HEIGHT 150

static void init(t_god *god)
{
	printf("[1] Jungle\n[2] Black & White\n[3] Red-Yellow Gradient\n[4] Full Random\n\nChoose the coloration: ");
	int i;
	scanf("%d", &i);
	if (i < 1 || i > 4) {
		printf("Wrong input. Try again.\n");
		exit(1);
	}
	god->coloris = i;
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, WWIDTH, WHEIGHT, "Ubuntu wallpaper");
	god->img = mlx_new_image(god->mlx, WWIDTH, WHEIGHT);
}

static int	get_triangle_not_filled(t_triangle *triangles, int size)
{
	for (int i = 0; i < size; i++)
		if (triangles[i].around != 7)
			return i;
	return -1;
}

static void update(t_god *god)
{
	t_triangle *triangles = malloc(sizeof(t_triangle));

	/// First Triangle
	t_rect rect;
	rect.ul = (t_point){450, 233};
	rect.width = 1.5f * RECT_HEIGHT;
	rect.height = RECT_HEIGHT;
	rect.angle = 0;
	triangles[0] = generate_and_draw_triangle(rect, god->img, NULL, triangles, 1, god->coloris);

	for (int i = 1; i < 2000; i++)
	{
		int	t_i = get_triangle_not_filled(triangles, i);
		int pt_i = fmin(((~triangles[t_i].around) & 7) / 2, 2);
		t_point base[2] = {triangles[t_i].pts[pt_i], triangles[t_i].pts[(pt_i + 1) % 3]};
		rect.ul = base[0];
		t_point	base_v = minus(base[1], base[0]);
		rect.width = norm(base_v);
		rect.height = RECT_HEIGHT;
		rect.angle = atan2(base_v.y, base_v.x);
		// Orienting the rect
		t_point height_v = {0, rect.height};
		height_v = rotate(height_v, rect.angle);
		if (dot(height_v, minus(triangles[t_i].pts[(pt_i + 2) % 3], rect.ul)) > 0)
			rect.height *= -1;
		triangles = (t_triangle *)realloc(triangles, (i + 1) * sizeof(t_triangle));
		triangles[i] = generate_and_draw_triangle(rect, god->img, &base, triangles, i + 1, god->coloris);
		if (triangle_is_out_of_bounds(triangles[i], 0, WWIDTH, 0, WHEIGHT))
			triangles[i].around = 7;
		triangles[t_i].around |= (int)pow(2, pt_i);
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
