#pragma once
#include <vector>
#include <algorithm> 
#include <limits>
#include <iostream>
#include "math3d.h"
#include "scene.h"

class Renderer {
public:
	//fov in radians
	Renderer(int width, int height, float fov);
	~Renderer();
	void start();
	int save_to_file(char const *filename);
private:
	int _width = 0;
	int _height = 0;

	//pre-calculated X,Y coordinates of pixels' centers 
	//Vec3f* _pixel_coords = nullptr;
	//pre-calculated pixels' ray direction
	std::vector<Vec3f> _ray_directions;
	//color buffer
	uint8_t* _color_buffer = nullptr;
	int _channel_num = 3;
	//plane z coordinate (is calculated from fov and size)
	float _plane_z_coord = -1;
	float _fov = 0;
	Vec3f _origin = { 0, 0, 0 };
	Scene _scene;

};