#version 450 core

layout(location = 0) out vec4 OutColor;

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
	vec4 color = vec4(0.0f, 1.0f, 1.0f, 1.0f);
	OutColor = Clamp(color, 0.0f, 1.0f);
}
