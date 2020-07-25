#include "renderer.h"
#include <iostream>
#include "light.h"

int main() {
	Renderer renderer = Renderer(5000, 5000, 3.14f/2.0f);
	renderer.start();
	int succeed = renderer.save_to_file("out.png");
	std::cout << succeed << std::endl;
	getchar();
	return 0;
}