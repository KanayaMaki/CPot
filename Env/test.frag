#version 430 core

in vec2 UV;

layout(location = 0) out vec4 color;

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
    float Timer;
};


layout(binding = 0) uniform sampler2D DiffuseTexture;

void main() {
	color = texture( DiffuseTexture, UV ) * Diffuse;
}