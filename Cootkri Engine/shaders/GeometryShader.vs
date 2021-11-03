#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in float texID;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
flat out int TexID;

uniform mat4 transMatrix, rotMatrix, viewMatrix;

void main(){

	FragPos = vec3(transMatrix * vec4(position, 1.0));
	TexCoords = texCoord;
	TexID = int(texID);
	Normal = vec3(rotMatrix * vec4(normal, 1.0));
	gl_Position = viewMatrix * vec4(FragPos, 1.0);

}