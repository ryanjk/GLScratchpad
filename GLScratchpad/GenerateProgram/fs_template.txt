#version 450 core

in V2F {
	vec4 N;
	vec4 worldPos;
} v2f;

out vec4 color;

void main(void) {
	color = vec4(1.0, 1.0, 1.0, 1.0);
}