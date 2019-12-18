#version 420
layout (location = 0) in vec3 position;

out vec3 uv;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    uv = position;

    gl_Position = projection * view * vec4(position, 1.0);
}  