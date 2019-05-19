#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>

#include <GL/gl.h>
#include <glm/glm.hpp>

bool load_object(const std::string& path, std::vector<GLfloat> &vertices, glm::vec3& size){
	std::ifstream inFile(path);
	if(!inFile){
		std::cout << "Failed to open " << path << std::endl;
		return false;
	}

	std::vector <std::array<GLfloat, 3>> temp_vertices;
	std::vector <std::array<int, 3>> temp_indices;

	glm::vec3 minimas(std::numeric_limits<GLfloat>::max(),
					  std::numeric_limits<GLfloat>::max(),
					  std::numeric_limits<GLfloat>::max());
	glm::vec3 maximas(std::numeric_limits<GLfloat>::min(),
					  std::numeric_limits<GLfloat>::min(),
					  std::numeric_limits<GLfloat>::min());

	std::string type;
	while(inFile >> type) {
		char lineHeader[128];
		if(type == "v") {
			GLfloat x, y, z;
			inFile >> x >> y >> z;

			minimas.x = std::min(minimas.x, x);
			minimas.y = std::min(minimas.y, y);
			minimas.z = std::min(minimas.z, z);

			maximas.x = std::max(maximas.x, x);
			maximas.y = std::max(maximas.y, y);
			maximas.z = std::max(maximas.z, z);

			temp_vertices.push_back({x, y, z});
		} else if(type == "f") {
			std::array<int, 3> indices;
			inFile >> indices[0];
			inFile >> indices[1];
			inFile >> indices[2];

			temp_indices.push_back(indices);
		}
		inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	for(auto&& face : temp_indices) {
		for(const auto& v : face) {
			vertices.push_back(temp_vertices[v - 1][0]);
			vertices.push_back(temp_vertices[v - 1][1]);
			vertices.push_back(temp_vertices[v - 1][2]);
		}
	}

	size = maximas - minimas;
	return true;
}

bool load_object(const std::string& path, std::vector<GLfloat>& vertices) {
	glm::vec3 size;
	return load_object(path, vertices, size);
}