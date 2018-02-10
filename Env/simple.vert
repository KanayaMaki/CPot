#version 450 core

layout(location = 0) in vec3 InPosLoc;

void main() {
	gl_Position =  vec4(InPosLoc, 1.0);
}
