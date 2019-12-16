#version 430

const int chunkSize = 64;

layout( location = 0 ) in ivec2 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform int resolution;

layout (std430, binding = 0) buffer HeightsBlock 
{
	vec4 values[(chunkSize + 1) * (chunkSize + 1)];
	vec4 UVs[(chunkSize + 1) * (chunkSize + 1)];
};

out vec3 normal;
out vec3 fragPosition;
out vec2 uv;

vec3 CalculateNormalForVertex(int index, int x, int y);

void main () {

	int x = position.x;
	int y = position.y;
	int index = y + (chunkSize + 1) * x;

	vec4 truePosition = vec4(x, values[index].x, y, 1.0);

	normal = CalculateNormalForVertex(index, x, y);

	uv = vec2(x, y);

	gl_Position = projection * view * model * truePosition;

	fragPosition = vec3(model * truePosition);
}

vec3 CalculateNormal(vec3 vertex, vec3 v1, vec3 v2) {
	return cross (v1 - vertex, v2 - vertex);
	//return ( cross(vertex, v1) - cross(vertex, v2) );
};

vec3 CalculateNormalForVertex(int index, int x, int y) {
	vec3 v1 = vec3(x, values[index].x, y);

	vec3 v2;
	vec3 v3;

	int chunkWidth = chunkSize + 1;

	if (x == chunkSize && y == chunkSize) {
		int vX = x - 1;
		int vY = y - 1;
		v2 = - vec3(x, values[vY + chunkWidth*x].x, vY);
		v3 = - vec3(vX, values[y + chunkWidth*vX].x, y);
	} else if (x != chunkSize && y == chunkSize) {
		int vX = x + 1;
		int vY = y - 1;
		v2 = vec3(x, values[vY + chunkWidth*x].x, vY);
		v3 = - vec3(vX, values[y + chunkWidth*vX].x, y);
	} else if (x == chunkSize && y != chunkSize) {
		int vX = x - 1;
		int vY = y + 1;
		v2 = - vec3(x, values[vY + chunkWidth*x].x, vY);
		v3 = vec3(vX, values[y + chunkWidth*vX].x, y);
	} else if (x != chunkSize && y != chunkSize) {
		int vX = x + 1;
		int vY = y + 1;
		v2 = vec3(x, values[vY + chunkWidth*x].x, vY);
		v3 = vec3(vX, values[y + chunkWidth*vX].x, y);
	}

	return CalculateNormal(v1, v2, v3);
};