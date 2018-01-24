#version 430 core

layout(location = 0) in vec3 InPosWor;
layout(location = 1) in vec3 InNorWor;
layout(location = 2) in vec2 InTexCoord;

layout(location = 0) out vec4 OutColor;

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
	vec3 CameraPosition;
	float _Dummy1;
	vec3 ToLight;
	float _Dummy3;
	vec3 CameraPositionLoc;
	float _Dummy4;
};


layout(binding = 0) uniform sampler2D DiffuseTexture;
layout(binding = 1) uniform sampler2D ToonTexture;



float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float HalfLambert(vec3 aNormal, vec3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	float halfLambert = pow((lambert * 0.5f + 0.5f), 2);
	return halfLambert;
}


void main() {

	float lighting = HalfLambert(InNorWor, -LightDirection);
	vec4 toonTexel = texture(ToonTexture, vec2(lighting, 1.0f - (1.0f - lighting)));

	vec4 diffuseTexel = texture(DiffuseTexture, vec2(InTexCoord.x, 1.0f - InTexCoord.y));
	
	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	color.xyz *= toonTexel.xyz;

	OutColor = color;
}