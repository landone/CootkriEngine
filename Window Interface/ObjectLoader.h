#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <map>

#include "Texture.h"

class ObjectLoader {
public:

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct Object {
		std::string name;
		std::string material;
		Texture texture;
		std::vector<unsigned int> indices;
	};

	struct ObjectFileData {
		std::vector<glm::vec3> position;
		std::vector<glm::vec2> texCoord;
		std::vector<glm::vec3> normal;
		std::map<std::string, Texture> textures;
	};

	static bool LoadOBJ(const std::string& pathway, std::vector<Object>& objects, std::vector<Vertex>& vertices);

private:

	/// <summary>
	/// Split a line into substrings separated by whitespace.
	/// </summary>
	/// <param name="line">Line to split</param>
	/// <returns>Vector of substrings</returns>
	static std::vector<std::string> SplitLine(const std::string& line);

	static std::vector<unsigned int> SplitFaceVertex(const std::string&);

	static bool ParseOBJLine(const std::vector<std::string>& args, std::vector<Object>&, ObjectFileData& d, std::vector<Vertex>&);

	static bool ParseVertex(const std::vector<std::string>& args, ObjectFileData& d);

	static bool ParseTextureCoord(const std::vector<std::string>& args, ObjectFileData& d);

	static bool ParseNormal(const std::vector<std::string>& args, ObjectFileData& d);

	static bool ParseFace(const std::vector<std::string>& args, std::vector<Object>&, ObjectFileData& d, std::vector<Vertex>&);

	static bool ParseMaterialFile(const std::vector<std::string>& args, ObjectFileData& d);

};