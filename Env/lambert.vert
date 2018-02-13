#version 450 core
layout(location = 0) in vec3 InPos;
layout(location = 1) in vec3 InNor;
layout(location = 2) in vec2 InTex;

layout(location = 0) out vec4 OutPosWor;
layout(location = 1) out vec4 OutNorWor;
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


vec4 MultiP(vec4 aVector, mat4x4 aMatrix) {
	return aVector * aMatrix;
}
mat4x4 CreateMatrixP(vec3 aVecX, vec3 aVecY, vec3 aVecZ) {
	mat4x4 lMatrix = mat4x4(
		vec4(aVecX.x, aVecX.y, aVecX.z, 0.0),
		vec4(aVecY.x, aVecY.y, aVecY.z, 0.0),
		vec4(aVecZ.x, aVecZ.y, aVecZ.z, 0.0),
		vec4(0.0, 0.0, 0.0, 1.0)
	);
	return transpose(lMatrix);
}
float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return clamp(lambert, 0.0, 1.0);
}
float HalfLambert(float aLighting) {
	float halfLambert = pow((aLighting * 0.5 + 0.5), 2);
	return halfLambert;
}
float HalfLambert(vec3 aNormal, vec3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	return HalfLambert(lambert);
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
	

	OutPosWor = MultiP(vec4(InPos, 1.0), World);

	gl_Position = MultiP(OutPosWor, View);
	gl_Position = MultiP(gl_Position, Projection);

	OutNorWor = MultiP(vec4(InNor, 1.0), NorWorld);

	OutTex = InTex;

	return;
}