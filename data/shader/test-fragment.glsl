#version 420

const vec4 FogColor = vec4(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);

const float FogMax = 192.0;

const float FogMin = 162.0;

const vec3 ambient = vec3(0.3, 0.3, 0.3);

const float specularStrength = 0.01;

const vec3 lightColor = vec3(0.8, 0.8, 0.8);

uniform vec3 theSun; 

uniform vec3 cameraPosition;

uniform sampler2D grassTexture;

uniform sampler2D rockTexture;

uniform sampler2D dirtTexture;

uniform sampler2D snowTexture;

in vec3 normal;
in vec3 fragPosition;
in vec2 uv;

in float mixRatio;

out vec4 finalColor;

float GetFogFactor(float d)
{
    if (d >= FogMax) return 1;
    if (d <= FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

vec4 GetTexturedSurface(in vec3 norm, in vec3 lighting) {
	vec4 dirtLayer, groundLayer, result;

	if (fragPosition.y >= 105.0) {
		dirtLayer = mix(texture2D(dirtTexture, uv), texture2D(snowTexture, uv), smoothstep(105.0, 115.0, fragPosition.y));
	} else {
		dirtLayer = texture2D(dirtTexture, uv);
	}
	
	float groundLayerMixAmount;

	if (fragPosition.y >= 90.0) {
		groundLayerMixAmount = smoothstep(85.0, 98.0, fragPosition.y);
	} else {
		groundLayerMixAmount = smoothstep(0.6, 0.8, acos(dot(vec3(0, 1, 0), norm)));
	}

	groundLayer = mix(texture2D(grassTexture, uv), dirtLayer, groundLayerMixAmount);

	result = mix(groundLayer, texture2D(rockTexture, uv), smoothstep(0.75, 0.90, acos(dot(vec3(0, 1, 0), norm)))) * vec4(lighting, 1.0);

	return result;
}

void main () {
	vec3 viewDir = normalize(cameraPosition - fragPosition);
	vec3 reflectDir = reflect(- theSun, normal);

	vec3 norm = normalize(normal);
	vec3 lightDir = theSun;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);

	float diffuse = max(dot(norm, lightDir), 0.0);

	vec3 specular = specularStrength * spec * lightColor;

	vec3 resultLight = (ambient + diffuse + specular) * lightColor;

	float fogAmount = GetFogFactor(distance(cameraPosition, fragPosition));

    finalColor = mix(GetTexturedSurface(norm, resultLight), FogColor, fogAmount);
}