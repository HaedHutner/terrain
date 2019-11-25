#version 420

const vec3 theSun = vec3(-0.75, 0.25, -0.75); 

in vec3 normal;

out vec4 finalColor;

void main () {
	vec3 norm = normalize(normal);
	vec3 lightDir = theSun;

	float diffuse = max(dot(norm, lightDir), 0.0);

	vec3 result = (vec3(0.1, 0.1, 0.1) + diffuse) * vec3(0.2, 0.8, 0.0);

    finalColor = vec4(result, 1.0);
}