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

//  The "saturation" parameter works like this:
//    0.0 creates a black-and-white image.
//    0.5 reduces the color saturation by half.
//    1.0 causes no change.
//    2.0 doubles the color saturation.
static void	saturate(t_color *color, float saturation)
{
	const float Pr = 0.299, Pg = 0.587, Pb = 0.114;
	double		P = sqrt(color->red * color->red * Pr
	  					+ color->green * color->green * Pg
						+ color->blue * color->blue * Pb);

	color->red = P + (color->red - P) * saturation;
	color->green = P + (color->green - P) * saturation;
	color->blue = P + (color->blue - P) * saturation;
}

static t_point	generate_rand_pt_in_rect(t_rect r)
{
	const int min_height = 20;
	t_point vs_flat = {rand() % r.width, min_height + rand() % (r.height - min_height)};
	if (r.height < 0)		// permet de facilement gerer
		vs_flat.y *= -1;	// le sens de la hauteur du rectangle
	t_point vs = rotate(vs_flat, r.angle);
	t_point res = {r.ul.x + vs.x, r.ul.y + vs.y};
	res.x = (int)res.x;		// permet d'eviter
	res.y = (int)res.y;		// les bugs d'affichage
	return res;
}

t_triangle	generate_and_draw_triangle(t_rect rect, void *img, const t_point (*base)[2], t_triangle *triangles, int size, int coloris)
{
	static int	cpt;
	t_triangle	triangle;

	/// Differents coloris
	t_color rand_color;
	if (coloris == 1)	// Jungle
	{
		int	rand_red = rand() % 256;
		rand_color = (t_color){rand_red, rand_red == 0 ? 0 : rand() % rand_red, 0};
	}
	else if (coloris == 2)	// Black & White
	{
		int	rand_c = rand() % 256;
		rand_color = (t_color){rand_c, rand_c, rand_c};
	}
	else if (coloris == 3)	// Red-Yellow Gradient
		rand_color = (t_color){255, rand() % 256, 0};
	else if (coloris == 4)	// Pastel
	{
		rand_color = (t_color){rand() % 256, rand() % 256, rand() % 256};
		saturate(&rand_color, 1.1f);
		rand_color.red = (rand_color.red + 255) / 2.f;
		rand_color.green = (rand_color.green + 255) / 2.f;
		rand_color.blue = (rand_color.blue + 255) / 2.f;
	}
	else if (coloris == 5)	// Full Random
		rand_color = (t_color){rand() % 256, rand() % 256, rand() % 256};

	if (base == NULL) {
		triangle.pts[0] = generate_rand_pt_in_rect(rect);
		triangle.pts[1] = generate_rand_pt_in_rect(rect);
		triangle.around = 0;
	}
	else {
		triangle.pts[0] = (*base)[0];
		triangle.pts[1] = (*base)[1];
		triangle.around = 1;
	}
	triangle.pts[2] = generate_rand_pt_in_rect(rect);

	for (int i = 0; i < size - 1; i++)
		if (triangles_collide(triangle, triangles[i])) {
			int pt_id = find_same_pt_in_triangles(triangles[i], triangle);
			if (pt_id != -1)
				triangles[i].around |= (int)pow(2, pt_id);
			pt_id = find_same_pt_in_triangles(triangle, triangles[i]);
			if (pt_id != -1)
				triangle.around |= (int)pow(2, pt_id);
			triangle.pts[2] = triangles[i].pts[2];
		}

	if (pts_are_equal(triangle.pts[2], triangle.pts[0])		// permet d'eviter de creer un rect
		|| pts_are_equal(triangle.pts[2], triangle.pts[1]))	// ou deux points se collisionnent
	{
		cpt++;
		if (cpt > 3) {
			triangle.around = 7;
			return triangle;
		}
		return generate_and_draw_triangle(rect, img, base, triangles, size, coloris);
	}
	cpt = 0;

	int dont_draw = 0;
	for (int i = 0; i < size; i++)
		if (triangles_are_equal(triangle, triangles[i])) {
			dont_draw = 1;
			break;
		}

	int x_min = WWIDTH - 1, x_max = 0, y_min = WHEIGHT - 1, y_max = 0;
	for (int i = 0; i < 3; i++) {
		if (triangle.pts[i].x < x_min)
			x_min = triangle.pts[i].x;
		if (triangle.pts[i].x > x_max)
			x_max = triangle.pts[i].x;
		if (triangle.pts[i].y < y_min)
			y_min = triangle.pts[i].y;
		if (triangle.pts[i].y > y_max)
			y_max = triangle.pts[i].y;
	}
	if (!dont_draw)
		for (int x = fmax(x_min, 0); x < fmin(x_max, WWIDTH); x++)
			for (int y = fmax(y_min, 0); y < fmin(y_max, WHEIGHT); y++)
				if (bsp(triangle.pts, (t_point){x, y}))
					mlx_put_pixel_img(img, x, y, rand_color);
	
	return triangle;
}

// Only for debug
void draw_pts_rect(t_rect rect, void *img)
{
	t_color purple = {127, 0, 255};

	t_point tmp;
	for (int i = 0; i < 1000; i++) {
		tmp = generate_rand_pt_in_rect(rect);
		if (tmp.x >= 0 && tmp.x <= WWIDTH && tmp.y >= 0 && tmp.y <= WHEIGHT)
			mlx_put_pixel_img(img, tmp.x, tmp.y, purple);
	}
}
