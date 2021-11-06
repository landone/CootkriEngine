#version 400 core

#define MAX_TEXTURES	16

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D textures[MAX_TEXTURES];
uniform vec3 tint;

void main(){
	
	vec4 origColor = texture(textures[0], TexCoords);
	if(origColor.a < 1){
		discard;
	}

	gPosition = vec4(FragPos, 1);
	gNormal = vec4(normalize(Normal), 1);
	gColor = vec4(origColor.xyz * tint, origColor.a);
	
}