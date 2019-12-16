#version 420

const vec3 ambient = vec3(0.3, 0.3, 0.3);

const float specularStrength = 0.01;

const vec3 lightColor = vec3(0.2, 0.8, 0.0);

uniform vec3 theSun; 

uniform vec3 cameraPosition;

uniform sampler2D colorTexture;

in vec3 normal;
in vec3 fragPosition;
in vec2 uv;

out vec4 finalColor;

void main () {
	vec3 viewDir = normalize(cameraPosition - fragPosition);
	vec3 reflectDir = reflect(- theSun, normal);
	vec3 rgb_normal = normal * 0.5 + 0.5;

	vec3 norm = normalize(normal);
	vec3 lightDir = theSun;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);

	float diffuse = max(dot(norm, lightDir), 0.0);

	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * lightColor;

    finalColor = vec4(result, 1.0);
}