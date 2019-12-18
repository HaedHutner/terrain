#version 420
out vec4 finalColor;

in vec3 uv;

uniform samplerCube skyboxTexture;

void main()
{    
    finalColor = texture(skyboxTexture, uv);
}