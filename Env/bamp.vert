#version 430 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 InPosLoc;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec3 InTanLoc;
layout(location = 3) in vec3 InBiNorLoc;
layout(location = 4) in vec2 InTexCoord;

layout(location = 0) out vec3 OutPosWor;
layout(location = 1) out vec3 OutNorLoc;
layout(location = 2) out vec3 OutTanLoc;
layout(location = 3) out vec3 OutBiNorLoc;
layout(location = 4) out vec2 OutTexCoord;

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
	vec4 lPosWor = mul(vec4(InPosLoc, 1), World);
	OutPosWor = lPosWor.xyz / lPosWor.w;

	vec4 lPosView = mul(lPosWor, View);
	vec4 lPosProj = mul(lPosView, Proj);
	gl_Position =  lPosProj;

	OutNorLoc = InNorLoc;
	OutTanLoc = InTanLoc;
	OutBiNorLoc = InBiNorLoc;

	OutTexCoord = InTexCoord;
}