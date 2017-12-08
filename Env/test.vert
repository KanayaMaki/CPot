#version 430 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 vertexPosition_MS;
layout(location = 1) in vec3 vertexNormal_MS;
layout(location = 2) in vec2 vertexUV;

out vec2 UV;

layout(binding = 0, column_major) uniform Data {
    mat4x4  World;
	mat4x4  View;
	mat4x4  Proj;
};
layout(binding = 1) uniform TmpData {
    vec4 Diffuse;
};

void main() {
	vec4 pos = mul(vec4(vertexPosition_MS, 1), World);
	pos = mul(pos, View);
	gl_Position =  mul(pos, Proj);
	//gl_Position = vec4(vertexPosition_MS, 1);
	UV = vertexUV;
}