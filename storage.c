#include "minirt.h"

void	init_scene(struct s_scene *scene)
{
	static t_cam	cams[1000];
	static t_light	lights[1000];

	scene->st.cams = cams;
	scene->st.lights = lights;
}
