#version 450 core

in V2F {
	vec4 N;
	vec4 worldPos;
	vec2 uv;
} v2f;

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;

uniform vec3 light_pos;
uniform vec4 view;

uniform vec3 ambient_c = vec3(1.0, 1.0, 1.0);
uniform float ambient_i;

uniform float diffuse_i;

uniform vec3 specular_c = vec3(1.0, 1.0, 1.0);
uniform float specular_i;

out vec4 color;

void main(void) {
	vec3 normal = normalize(v2f.N.xyz);
	vec3 light_dir = normalize(light_pos - v2f.worldPos.xyz);
	float n_dot_l = max(dot(normalize(light_dir), normal), 0.0);
	vec3 diffuse = n_dot_l * diffuse_i * texture2D(diffuse_map, v2f.uv).rgb;
	
	vec3 h = normalize(view.xyz + light_dir);
	float h_dot_n = max(dot(h, normal), 0.0);
	vec3 specular = specular_c * pow(h_dot_n, specular_i);
	
	vec3 ambient = ambient_c * ambient_i;
	
	vec3 final = diffuse + ambient + specular;
	color = vec4(final, 1.0);
}