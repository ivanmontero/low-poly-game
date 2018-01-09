#version 330 core
out vec4 color;
in vec3 pos;
in vec3 Normal;
flat in vec3 vcolor;
//in vec3 vcolor;

uniform vec3 Color;

void main() {
	// Lighting
	vec3 amb = vec3(.1) * vcolor;
	vec3 diff = vec3(.8) * vcolor;

	vec3 ld = -vec3(-0.2f, -0.7f, -0.3f);
	float d = max(dot(Normal, ld), 0.0);
	vec3 diffuse = diff * d;
	
	color = vec4(amb + diffuse, 1.0);

	//if(Normal.y > 0) 
	//	color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	//else
	//	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);


 //   color = vec4(Color, 1.0);
	//if(pos.y < -2.5)
	//	color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
} 
