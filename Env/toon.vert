#version 430 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 PosMod;
layout(location = 1) in vec3 NorMod;
layout(location = 2) in vec2 UVMod;

out vec3 PosWor;
out vec3 NorWor;
out vec2 UV;

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
	float _Dummy0;
    float Timer;
};

void main() {
	vec4 lPosWor = mul(vec4(PosMod, 1), World);
	PosWor = lPosWor.xyz / lPosWor.w;

	vec4 lPosView = mul(lPosWor, View);
	vec4 lPosProj = mul(lPosView, Proj);
	gl_Position =  lPosProj;

	vec4 lNorWor = mul(vec4(NorMod, 1), NorWorld);
	NorWor = lNorWor.xyz / lNorWor.w;

	UV = UVMod;
}