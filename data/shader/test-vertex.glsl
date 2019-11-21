#version 410

const uint chunkSize = 64;

layout( location = 0 ) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float heights[chunkSize * chunkSize];

void main () {
	gl_Position = projection * view * model * vec4(position, 1.0);
}