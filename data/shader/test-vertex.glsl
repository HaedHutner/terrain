#version 420

const int chunkSize = 64;

layout( location = 0 ) in ivec2 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform int resolution;

layout (std140, binding = 0) uniform HeightsBlock 
{
	vec4 values[chunkSize * chunkSize];
};

int chunkWidth = chunkSize / resolution;

out vec3 normal;

vec3 CalculateNormalForVertex(int index, int x, int y);

void main () {

	int x = position.x;
	int y = position.y;
	int index = y + chunkWidth * x;

	vec4 truePosition = vec4(x, values[index][0], y, 1.0);

	normal = CalculateNormalForVertex(index, x, y);

	gl_Position = projection * view * model * truePosition;	
}

vec3 CalculateNormal(vec3 vertex, vec3 v1, vec3 v2) {
	return -1 * cross (v1 - vertex, v2 - vertex);
	//return ( cross(vertex, v1) - cross(vertex, v2) );
};

vec3 CalculateNormalForVertex(int index, int x, int y) {
	vec3 v1 = vec3(x, values[index][0], y);

	vec3 v2;
	vec3 v3;

	if (x == 0 && y == 0) {
		v2 = - vec3(x + 2, values[y + 1 + chunkWidth*(x + 2)][0], y + 1);
		v3 = - vec3(x + 1, values[y + 2 + chunkWidth*(x + 1)][0], y + 2);
	}

	if (x != 0 && y == 0) {
		v2 = vec3(x - 1, values[y + chunkWidth*(x - 1)][0], y);
		v3 = - vec3(x, values[y + 1 + chunkWidth*x][0], y + 1);
	}

	if (x == 0 && y != 0) {
		v2 = - vec3(x - 1, values[y + chunkWidth*(x - 1)][0], y);
		v3 = vec3(x, values[y - 1 + chunkWidth*x][0], y - 1);
	}

	if (x != 0 && y != 0) {
		v2 = vec3(x - 1, values[y + chunkWidth*(x - 1)][0], y);
		v3 = vec3(x, values[y - 1 + chunkWidth*x][0], y - 1);
	}

	return CalculateNormal(v1, v2, v3);
};