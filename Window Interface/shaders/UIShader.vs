#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 transMatrix;
uniform float layer;
uniform vec4 texMod; //(Offset, Scale)

void main() {

	TexCoords = (texCoord * vec2(texMod.z, texMod.w)) + vec2(texMod.x, texMod.y);
	gl_Position = transMatrix * vec4(position, 1.0);
	gl_Position.z = layer;
	
}