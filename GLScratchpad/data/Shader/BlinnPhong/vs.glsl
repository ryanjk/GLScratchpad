#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv; 

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out V2F {
	vec4 N;
	vec4 worldPos;
	vec2 uv;
} v2f;

void main(void) {
	v2f.worldPos = m * vec4(position, 1.0);
	gl_Position = p * v * v2f.worldPos;
	v2f.N = inverse(transpose(m)) * vec4(normal.xyz, 0.0);
	v2f.uv = uv;
}