#version 420

const int chunkSize = 64;

layout( location = 0 ) in ivec2 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout ( binding = 0 ) uniform HeightsBlock 
{
	float values[chunkSize * chunkSize];
};

void main () {
	vec4 truePosition = vec4(
		position.x,
		100.0 * values[position.y + chunkSize * position.x], 
		position.y,
		1.0
	);

	gl_Position = projection * view * model * truePosition;
}