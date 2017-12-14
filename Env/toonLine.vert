#version 430 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 PosMod;
layout(location = 1) in vec3 NorMod;
layout(location = 2) in vec2 UVMod;

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
    float Timer;
};
layout(binding = 3) uniform Toon {
    float LineWidth;
	vec3 _Toon_Dummy0;
};

void main() {

	vec3 lPosModAdd = PosMod + normalize(NorMod) * LineWidth;

	vec4 lPosWor = mul(vec4(lPosModAdd, 1), World);
	vec4 lPosView = mul(lPosWor, View);
	vec4 lPosProj = mul(lPosView, Proj);

	gl_Position =  lPosProj;
}