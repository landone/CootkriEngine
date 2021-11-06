#include "ObjectLoader.h"

#include <fstream>

bool ObjectLoader::LoadOBJ(const std::string& pathway, std::vector<Object>& data, std::vector<Vertex>& vertices) {

	data.clear();
	vertices.clear();

	std::ifstream file(pathway);
	if (!file.is_open()) {
		return false;
	}
	std::string line;
	bool success = true;
	ObjectFileData counter;

	while (std::getline(file, line)) {

		std::vector<std::string> args = SplitLine(line);
		if (!ParseOBJLine(args, data, counter, vertices)) {
			success = false;
			break;
		}

	}

	//Assign textures to relevant objects
	for (int i = 0; i < data.size(); ++i) {
		if (counter.textures.find(data[i].material) != counter.textures.end()) {
			data[i].texture = counter.textures[data[i].material];
		}
	}

	file.close();
	return success;

}

bool ObjectLoader::ParseOBJLine(const std::vector<std::string>& args, std::vector<Object>& data, ObjectFileData& counter, std::vector<Vertex>& vertices) {

	if (args.size() < 2) {
		return true;
	}

	if (args[0] == "v") {
		if (!ParseVertex(args, counter)) {
			return false;
		}
	}
	else if (args[0] == "vt") {
		if (!ParseTextureCoord(args, counter)) {
			return false;
		}
	}
	else if (args[0] == "vn") {
		if (!ParseNormal(args, counter)) {
			return false;
		}
	}
	else if (args[0] == "o") {
		data.push_back(Object());
		data.back().name = args[1];
	}
	else if (args[0] == "g") {
		data.push_back(Object());
		data.back().name = args[1];
	}
	else if (args[0] == "f") {
		if (!ParseFace(args, data, counter, vertices)) {
			return false;
		}
	}
	else if (args[0] == "usemtl") {
		if (data.size() == 0) {
			data.push_back(Object());
		}
		data.back().material = args[1];
	}
	else if (args[0] == "mtllib") {
		if (!ParseMaterialFile(args, counter)) {
			return false;
		}
	}

	return true;

}

bool ObjectLoader::ParseVertex(const std::vector<std::string>& args, ObjectFileData& counter) {

	glm::vec3 result;
	try {
		result.x = std::stof(args[1]);
		result.y = std::stof(args[2]);
		result.z = std::stof(args[3]);
	}
	catch(...) {
		return false;
	}

	counter.position.push_back(result);

	return true;

}

bool ObjectLoader::ParseTextureCoord(const std::vector<std::string>& args, ObjectFileData& counter) {

	glm::vec2 result;
	try {
		result.x = std::stof(args[1]);
		result.y = std::stof(args[2]);
	}
	catch (...) {
		return false;
	}

	counter.texCoord.push_back(result);

	return true;

}

bool ObjectLoader::ParseNormal(const std::vector<std::string>& args, ObjectFileData& counter) {

	glm::vec3 result;
	try {
		result.x = std::stof(args[1]);
		result.y = std::stof(args[2]);
		result.z = std::stof(args[3]);
	}
	catch (...) {
		return false;
	}

	counter.normal.push_back(result);

	return true;

}

bool ObjectLoader::ParseFace(const std::vector<std::string>& args, std::vector<Object>& data, ObjectFileData& counter, std::vector<Vertex>& vertices) {

	if (args.size() < 4) {
		return false;
	}

	if (data.size() == 0) {
		data.push_back(Object());
	}

	bool quad = false;

	for (int i = 1; i <= 4; ++i) {

		//Quadrangle check
		if (i == 4 && args.size() < 5) {
			break;
		}

		std::vector<unsigned int> indices = SplitFaceVertex(args[i]);
		if (indices.size() < 3) {
			return false;
		}

		if ((indices[0] >= counter.position.size()) || (indices[1] >= counter.texCoord.size()) ||
			(indices[2] >= counter.normal.size())) {
			return false;
		}

		vertices.push_back(Vertex());
		Vertex& vert = vertices.back();
		vert.position = counter.position[indices[0]];
		vert.texCoord = counter.texCoord[indices[1]];
		vert.normal = counter.normal[indices[2]];

		if (i == 4) {
			quad = true;
		}

	}

	Object& obj = data.back();
	unsigned int end = vertices.size() - 1;

	obj.indices.push_back(end);
	obj.indices.push_back(end - 1);
	obj.indices.push_back(end - 2);
	obj.indices.push_back(end - 2);
	obj.indices.push_back(end - 1);
	obj.indices.push_back(end);

	//Face is quad, make a second triangle
	if (quad) {
		obj.indices.push_back(end);
		obj.indices.push_back(end - 3);
		obj.indices.push_back(end - 2);
		obj.indices.push_back(end - 2);
		obj.indices.push_back(end - 3);
		obj.indices.push_back(end);
	}

	return true;

}

std::vector<unsigned int> ObjectLoader::SplitFaceVertex(const std::string& input) {

	std::vector<unsigned int> result;
	std::string current;
	for (int i = 0; i < input.size(); ++i) {
		char c = input[i];
		if (c == '/') {
			try {
				result.push_back(std::stoi(current) - 1);
				current.clear();
			}
			catch (...) {
				result.clear();
				return result;
			}
		}
		else {
			current.push_back(c);
		}
	}

	if (current.size() > 0) {
		try {
			result.push_back(std::stoi(current) - 1);
			current.clear();
		}
		catch (...) {
			result.clear();
			return result;
		}
	}

	return result;

}

std::vector<std::string> ObjectLoader::SplitLine(const std::string& line) {

	std::vector<std::string> result;
	std::string currentStr = "";

	for (unsigned int i = 0; i < line.size(); ++i) {
		char c = line[i];
		if (c == ' ' || c == '\t') {
			//Whitespace
			if (!currentStr.empty()) {
				result.push_back(currentStr);
				currentStr.clear();
			}
		}
		else {
			currentStr.push_back(c);
		}
	}

	if (!currentStr.empty()) {
		result.push_back(currentStr);
	}

	return result;

}

bool ObjectLoader::ParseMaterialFile(const std::vector<std::string>& args, ObjectFileData& counter) {

	std::ifstream file(args[1]);
	if (!file.is_open()) {
		return false;
	}

	std::string line;
	std::string currentMtl;

	while (std::getline(file, line)) {

		std::vector<std::string> args = SplitLine(line);
		if (args.size() < 2) {
			continue;
		}

		if (args[0] == "newmtl") {
			currentMtl = args[1];
		}
		else if (args[0] == "map_Kd") {
			counter.textures[currentMtl] = Texture(args[1]);
		}

	}

	file.close();
	return true;

}