#include "scene.h"

void Scene::add_sphere(const Vec3f& center, float radius, const Material& material) {
	obstacles.push_back(std::make_unique<Sphere>(center, radius, material));
}

void Scene::add_light_source(const Vec3f& position, float intensity) {
	lights.push_back(std::make_unique<LightSource>(position, intensity));
}

bool Scene::calc_reflected_color(const Vec3f& point, const Vec3f& reflection, int light_source_num, int reflecting_obstacle_num, unsigned int depth, Vec3i& color) {
	//in first iteration point == pixel_center

	if (depth == 0)
		return 0;

	//distance to the closest object in direction of ray from pixel's center
	float min_dist = std::numeric_limits<float>::max();

	bool reflects_something = false;
	for (int k = 0; k < obstacles.size(); k++) {

		//skip reflecting obstacle
		if (k == reflecting_obstacle_num)
			continue;

		//distance to the current object in direction of ray from pixel's center
		float current_dist = -1.0f;
		color = { 0, 0, 0 };

		//norm in point of intersection
		Vec3f normal = { 0.0f, 0.0f, 0.0f };
		obstacles[k]->calc_norm(point, normal);

		//calculate light direction
		Vec3f light_dir = { 0.0f, 0.0f, 0.0f };
		substract(lights[light_source_num]->position, point, light_dir);
		light_dir.normalize();

		Vec3f new_reflection = { 0.0f, 0.0f, 0.0f };
		calc_reflection(light_dir, normal, new_reflection);
		bool intersects = 0;//cast_ray(point, new_reflection, k, current_dist, color);
		if (intersects && current_dist < min_dist && current_dist > 0.0f) {
			calc_reflected_color(point, reflection, light_source_num, reflecting_obstacle_num, depth - 1, color);
			reflects_something = true;
			min_dist = current_dist;
		}
	}

	return reflects_something;
}

bool Scene::cast_ray(const Vec3f& origin, const Vec3f& dir, int k, unsigned int depth, float& distance, Vec3i& color) {

	if (depth == 0)
		return 0;

	//point of intersection
	Vec3f x;
	//if ray intersects the obstacle, change pixel color and add lighting
	bool intersects = obstacles[k]->ray_intersects(origin, dir, x);
	if (intersects) {
		distance = calc_distance(x, origin);

		color = obstacles[k]->color;

		//apply Phong reflection
		float diffuse_intensity = 0.0f;
		float specular_intensity = 0.0f;
		for (int m = 0; m < lights.size(); m++) {
			////apply shadows
			////check if light direction intersects other objects: if it does, skip current light source
			//bool skip = false;
			//for (int q = 0; q < _scene.obstacles.size() && skip == false; q++) {
			//	if (q == k)
			//		continue;
			//	skip = _scene.obstacles[q]->ray_intersects(x, _scene.lights[m]->position);
			//}
			//if (skip)
			//	continue;

			//norm in point of intersection
			Vec3f normal = { 0.0f, 0.0f, 0.0f };
			obstacles[k]->calc_norm(x, normal);

			//calculate light direction
			Vec3f light_dir = { 0.0f, 0.0f, 0.0f };
			substract(lights[m]->position, x, light_dir);
			light_dir.normalize();

			//calculate reflection vector R = 2(N*L)N-L
			Vec3f reflection = { 0.0f, 0.0f, 0.0f };
			calc_reflection(light_dir, normal, reflection);

			//calculate reflection color
			Vec3i reflection_color = { 0, 0, 0 };
			float reflected_distance = 0.0f;
			bool reflection_succeed = cast_ray(x, reflection, k, depth - 1, reflected_distance, reflection_color);

			//calculate diffuse light intensity: dot product between light direction and norm 
			//at the point of intersection
			diffuse_intensity += lights[m]->intensity
				* std::max(0.0f, dot_product(light_dir, normal)) * obstacles[k]->albedo;

			//calculate specular intensity
			specular_intensity += lights[m]->intensity *
				std::powf(std::max(0.0f, dot_product(dir, reflection)), obstacles[k]->n_specular);

			//apply illumination and reflection color
			float diffuse_illum = diffuse_intensity * obstacles[k]->Kd;
			float specular_illum = specular_intensity * obstacles[k]->Ks;
			int R = obstacles[k]->color.R * diffuse_illum + specular_illum + reflection_succeed * reflection_color.R * obstacles[k]->Kr;
			int G = obstacles[k]->color.G * diffuse_illum + specular_illum + reflection_succeed * reflection_color.G * obstacles[k]->Kr;
			int B = obstacles[k]->color.B * diffuse_illum + specular_illum + reflection_succeed * reflection_color.B * obstacles[k]->Kr;
			if (R > 255)
				R = 255;
			if (G > 255)
				G = 255;
			if (B > 255)
				B = 255;
			color = { R, G, B };
		}
	} 
	else {
		color = { -1, -1, -1 };
	}

	return intersects;
}