#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 transMatrix;
uniform float layer;

void main() {

	TexCoords = texCoord;
	gl_Position = transMatrix * vec4(position, 1.0);
	gl_Position.z = layer;
	
}