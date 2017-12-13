#version 430 core

in vec3 PosWor;
in vec3 NorWor;
in vec2 UV;

layout(location = 0) out vec4 outColor;

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


layout(binding = 0) uniform sampler2D DiffuseTexture;
layout(binding = 1) uniform sampler2D ToonTexture;



float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(-LightDirection);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float HalfLambert(vec3 aNormal, vec3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	float halfLambert = pow((lambert * 0.5f + 0.5f), 2);
	return halfLambert;
}


void main() {

	float lighting = HalfLambert(NorWor, -LightDirection);
	vec4 toonTexel = texture(ToonTexture, vec2(lighting, lighting));

	vec4 diffuseTexel = texture(DiffuseTexture, UV);
	
	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	color.xyz *= toonTexel.xyz;

	outColor = color;
}