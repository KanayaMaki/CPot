#version 450 core

layout(location = 0) in vec2 InTexCoord;

layout(location = 0) out vec4 OutColor;

layout(binding = 0, column_major) uniform Data {
    mat4x4  World;
	mat4x4  View;
	mat4x4  Proj;
	mat4x4  NorWorld;
};
layout(binding = 1) uniform Material {
    vec4 Diffuse;
};


layout(binding = 0) uniform sampler2D DiffuseTexture;


float Clamp(float aValue, float aMin, float aMax) {
	if(aValue < aMin) aValue = aMin;
	if(aValue > aMax) aValue = aMax;
	return aValue;
}

vec4 Clamp(vec4 aVector, float aMin, float aMax) {
	return vec4(
		Clamp(aVector.x, aMin, aMax),
		Clamp(aVector.y, aMin, aMax),
		Clamp(aVector.z, aMin, aMax),
		Clamp(aVector.w, aMin, aMax)
	);
}

void main() {

	vec4 diffuseTexel = texture(DiffuseTexture, vec2(InTexCoord.x, 1.0f - InTexCoord.y));

	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;

	OutColor = Clamp(color, 0.0f, 1.0f);
}
