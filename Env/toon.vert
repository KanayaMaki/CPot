#version 450 core
layout(location = 0) in vec3 InPos;
layout(location = 1) in vec3 InNor;
layout(location = 2) in vec2 InTex;

layout(location = 0) out vec3 OutPosWor;
layout(location = 1) out vec3 OutNorWor;
layout(location = 2) out vec2 OutTex;

layout(binding = 0, column_major) uniform cWVPBuffer {
	mat4x4 World;
	mat4x4 View;
	mat4x4 Projection;
	mat4x4 NorWorld;
};

layout(binding = 1, column_major) uniform cDiffuseBuffer {
	vec4 Diffuse;
};

layout(binding = 2, column_major) uniform cTimerBuffer {
	vec3 LightDirection;
	float _Dummy0;
	vec3 CameraPosition;
	float _Dummy1;
	vec3 ToLight;
	float _Dummy3;
	vec3 CameraPositionLoc;
	float _Dummy4;
};

layout(binding = 0) uniform sampler2D DiffuseTexture;
layout(binding = 1) uniform sampler2D ToonTexture;


vec4 MultiP(vec4 aVector, mat4x4 aMatrix) {
	return aVector * aMatrix;
}
float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return lambert;
}
float HalfLambert(vec3 aNormal, vec3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	float halfLambert = pow((lambert * 0.5 + 0.5), 2);
	return halfLambert;
}
float HalfLambert(float aLighting) {
	float halfLambert = pow((aLighting * 0.5 + 0.5), 2);
	return halfLambert;
}
vec3 MultiP(vec3 aVector, mat4x4 aMatrix) {
	vec4 lVector = MultiP(vec4(aVector, 1.0), aMatrix);
	return lVector.xyz / lVector.w;
}
float SpecularPhong(vec3 aToView, vec3 aNor, vec3 aToLight, int aSpecularPow) {
	vec3 halfVector = normalize(aToView + aToLight);
	float specular = pow(max(dot(aNor, halfVector), 0.0), int(aSpecularPow));
	return specular;
}
void main() {

	

	vec4 lPosWor = MultiP(vec4(InPos, 1.0), World);
	OutPosWor = lPosWor.xyz / lPosWor.w;

	vec4 lPosView = MultiP(lPosWor, View);
	vec4 lPosProj = MultiP(lPosView, Projection);
	gl_Position = lPosProj;

	vec4 lNorWor = MultiP(vec4(InNor, 1.0), NorWorld);
	OutNorWor = lNorWor.xyz / lNorWor.w;

	OutTex = InTex;

	return;
}