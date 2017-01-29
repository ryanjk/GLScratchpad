#version 450 core

in V2F {
	vec4 N;
	vec4 worldPos;
} v2f;

uniform vec3 light_pos;
uniform float shade;

out vec4 color;

void main(void) {
	vec3 normal = normalize(v2f.N.xyz);
	vec3 light_dir = normalize(light_pos - v2f.worldPos.xyz);
	float n_dot_l = max(dot(normalize(light_dir), normal), 0.0);
	vec3 diffuse = n_dot_l * shade * vec3(1.0, 1.0, 1.0);
	
	vec3 final = diffuse;
	color = vec4(final, 1.0);
}