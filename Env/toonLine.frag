#version 450 core

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
layout(binding = 2) uniform Other {
	vec3 LightDirection;
	float _Other_Dummy0;
	vec3 CameraPosition;
	float _Dummy1;
	vec3 ToLight;
	float _Dummy3;
	vec3 CameraPositionLoc;
	float _Dummy4;
};
layout(binding = 3) uniform Toon {
    float LineWidth;
	vec3 _Toon_Dummy0;
};


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

	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;

	OutColor = Clamp(color, 0.0f, 1.0f);
}
