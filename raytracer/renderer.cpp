#include "renderer.h"
#include "materials.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Renderer::Renderer(int width, int height, float fov) {
	_width = width;
	_height = height;
	_fov = fov;

	_plane_z_coord = _width / (2.0f * tanf(fov*0.5f));

	_scene.add_sphere(Vec3f(0.0f, 0.0f, _plane_z_coord + 2000.0f), 1000.0f, ICE_MATERIAL);
	_scene.add_sphere(Vec3f(-300.0f, -100.0f, _plane_z_coord + 500.0f), 100.0f, SHINY_CRIMSON_MATERIAL);
	_scene.add_light_source(Vec3f(500.0f, 500.0, _plane_z_coord - 150.0f), 5.0f);
	_scene.add_light_source(Vec3f(-700.0f, -700.0f, _plane_z_coord + 150.0f), 0.5f);

	_ray_directions.resize(_height*_width*_channel_num);
	_color_buffer = new uint8_t[_height*_width*_channel_num];

	int h_res = _height % 2;
	int w_res = _width % 2;
	bool height_is_even, width_is_even;

	h_res == 0 ? height_is_even = true : height_is_even = false;
	w_res == 0 ? width_is_even = true : width_is_even = false;

	float h_init_val, w_init_val;

	if (height_is_even)
		h_init_val = static_cast<float>(_height) * 0.5f - 0.5f;
	else
		h_init_val = static_cast<float>(_height) * 0.5f - 1.0f;

	if (width_is_even)
		w_init_val = -static_cast<float>(_width) * 0.5f + 0.5f;
	else
		w_init_val = -static_cast<float>(_width) * 0.5f + 1.0f;

	

	int index = 0;
	for (int i = 0; i < _height; i++) {
		float y = h_init_val - i;
		for (int j = 0; j < _width; j++) {
			//fill color buffer
			float r = (float)i / (float)width;
			float g = (float)j / (float)height;
			float b = 0.2f;
			int ir = int(255.99f * r);
			int ig = int(255.99f * g);
			int ib = int(255.99f * b);
			_color_buffer[index++] = ir;
			_color_buffer[index++] = ig;
			_color_buffer[index++] = ib;

			//calculate coords of each pixel's center
			Vec3f pixel_center = { w_init_val + j, y, _plane_z_coord };

			//calculate ray directions from each pixel's center 
			substract(pixel_center, _origin, _ray_directions[j + _height * i]);
			_ray_directions[j + _height * i].normalize();
		}
	}		
}

Renderer::~Renderer() {	
	delete[] _color_buffer;
}

void Renderer::start() {
	int index = 0;
	for (int i = 0; i < _height; i++) 
		for (int j = 0; j < _width; j++) {
			//distance to the closest object in direction of ray from pixel's center
			float min_dist = std::numeric_limits<float>::max();

			for (int k = 0; k < _scene.obstacles.size(); k++) {	
				//distance to the current object in direction of ray from pixel's center
				float current_dist = -1.0f;
				Vec3i color = { 0, 0, 0 };
				bool intersects = _scene.cast_ray(_origin, _ray_directions[j + _height * i], k,
					_scene.obstacles[k]->depth, current_dist, color);
				if (intersects && current_dist < min_dist && current_dist > 0.0f) {
					min_dist = current_dist;
					_color_buffer[index] = color.R;
					_color_buffer[index + 1] = color.G;
					_color_buffer[index + 2] = color.B;
				}
			}	
			index += 3;
		}
}

int Renderer::save_to_file(char const *filename) {
	return stbi_write_png(filename, _width, _height, _channel_num, _color_buffer, _width * _channel_num);
}