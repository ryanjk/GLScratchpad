#version 450 core

in V2F {
	vec4 N;
	vec4 worldPos;
} v2f;

uniform vec3 light_pos;
uniform float shade;

uniform sampler2D proj_texture; // the texture being projected

uniform mat4 tex_v; // the apex of the texture frustum
uniform mat4 tex_p; // the texture projection matrix
uniform mat4 bias; // bias matrix to transform to UV space

out vec4 color;

void main(void) {
	vec3 normal = normalize(v2f.N.xyz);
	vec3 light_dir = normalize(light_pos - v2f.worldPos.xyz);
	float n_dot_l = max(dot(normalize(light_dir), normal), 0.0);
	vec3 diffuse = n_dot_l * shade * vec3(1.0, 1.0, 1.0);
	
	// project the current point onto the texture, now it's in clip space
	vec4 projected = tex_p * tex_v * v2f.worldPos;
	vec3 tex_color;
	
	// clip the point if it's outside the texture's frustum
	if (abs(projected.x) > abs(projected.w) ||
		abs(projected.y) > abs(projected.w) ||
		abs(projected.z) > abs(projected.w)) {
		// NOTE: the 'culled' color depends on what you do with the texture's value
		// here I use white because I multiply it with the surface diffuse
		tex_color = vec3(1.0, 1.0, 1.0);
	}
	else {
		// transform the point to normalized device coordinates, then to UV space
		vec2 proj_uv = (bias * (projected / projected.w)).xy;
		
		tex_color = texture2D(proj_texture, proj_uv).rgb;	
	}

	vec3 final = diffuse * tex_color;
	color = vec4(final, 1.0);
}