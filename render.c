#include "minirt.h"
#include <math.h>

void	camray(t_global *global, t_ivec coord)
{
	t_ivec	reso;
	t_cam	cam;
	t_vec3 	dir;

	reso = global->parse.scene.reso;
	cam = global->parse.scene.st.cams[global->cam];
	dir.x = (2 * (coord.x + 0.5) / (float)reso.x - 1) * global->ratio * cam.scale;
	dir.y = (1 - 2 * (coord.y + 0.5) / (float)reso.y) * cam.scale;
	dir.z = -1;
	dir = transform(cam.mat, dir);
}

t_color	render(t_global *global, t_ivec coord)
{
	camray(global, coord);
	return ((t_color){100, 250, 200});
}
