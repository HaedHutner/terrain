#version 420

const vec3 ambient = vec3(0.3, 0.3, 0.3);

const float specularStrength = 0.01;

const vec3 lightColor = vec3(0.8, 0.8, 0.8);

uniform vec3 theSun; 

uniform vec3 cameraPosition;

uniform sampler2D grassTexture;

uniform sampler2D rockTexture;

uniform sampler2D dirtTexture;

in vec3 normal;
in vec3 fragPosition;
in vec2 uv;

in float mixRatio;

out vec4 finalColor;

void main () {
	vec3 viewDir = normalize(cameraPosition - fragPosition);
	vec3 reflectDir = reflect(- theSun, normal);

	vec3 norm = normalize(normal);
	vec3 lightDir = theSun;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);

	float diffuse = max(dot(norm, lightDir), 0.0);

	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * lightColor;

	vec4 grassLayer = mix(texture2D(grassTexture, uv), texture2D(dirtTexture, uv), mixRatio);

    finalColor = mix(texture2D(rockTexture, uv), grassLayer, step(0.9999, abs(atan(norm.y / norm.x)))) * vec4(result, 1.0);
}