#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 Color;

uniform float near;
uniform float far;

out vec3 pos;
out vec3 Normal;
flat out vec3 vcolor;
//out vec3 vcolor;

// "Fans" possibly from way that triangles are made?

float noise(vec2 p);

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	pos = position;
	Normal = normal;
	// color variation;
	float c = .1 * ( 2.0 * noise(vec2(position.x, position.z)) - 1.0);
	//c = 0;

	float elevation = (model * vec4(position, 1.0f)).y;
	float n = noise(vec2(position.x, position.z));

	if(elevation < -5)	// Water
		vcolor = vec3(0.2, 0.2, 1.0) + vec3(c * .25);
	else if (elevation < 5) // lerp between water and sand
		vcolor = vec3(mix(.2, 1, (elevation + 5) / 10), 
					  mix(.2, 1, (elevation + 5) / 10),
					  mix(.85, 1, 1 - (elevation + 5) / 10)) + vec3(c);
	else if (elevation < 15)	// Sand
		vcolor = vec3(1.0, 1.0, 0.85) + vec3(c);
	else if (elevation + n * 50 < 400)	// Green
		vcolor = vec3(0.0, 1.0, 0.0) + vec3(c);
	else if (elevation + n * 100 < 1100) // Rock
		vcolor = vec3(0.4, 0.4, 0.4) + vec3(c);
	else	// Snow
		vcolor = vec3(0.95, 0.95, 0.95) + vec3(c / 2);

	// OLD:
	// if(elevation < -.2)
	// 	vcolor = vec3(0.2, 0.2, 1.0) + vec3(c * .25);
	// else 
	// 	vcolor = vec3(0.0, 1.0, 0.0) + vec3(c);

	// To make sure distant traingles are culled correctly
	// Logarithmic depth buffer 1
	//gl_Position.z = 2.0*log(gl_Position.w/near)/log(far/near) - 1; 
    //gl_Position.z *= gl_Position.w;
	// Logarithmic depth buffer 2
	float C = 0.1f;
	gl_Position.z = (2*log(C*gl_Position.w + 1) / log(C*far + 1) - 1) * gl_Position.w;   //OpenGL, depth range -1..1
}


float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}