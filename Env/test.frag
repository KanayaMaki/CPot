#version 430 core

in vec2 UV;

layout(location = 0) out vec4 color;

layout(binding = 1) uniform TmpData {
    vec4 Diffuse;
};


layout(binding = 0) uniform sampler2D myTextureSampler;

void main() {
	color = texture( myTextureSampler, UV ) * Diffuse;
	//color = Diffuse;
}