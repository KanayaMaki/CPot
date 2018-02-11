#version 450 core

layout(location = 0) in vec3 InPosWor;
layout(location = 1) in vec3 InToLightTan;
layout(location = 2) in vec3 InToCameraTan;
layout(location = 3) in vec2 InTexCoord;

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
layout(binding = 1) uniform sampler2D BampTexture;


vec4 mul(vec4 aVector, mat4x4 aMatrix) {
	return aVector * aMatrix;
}
vec3 mul(vec3 aVector, mat4x4 aMatrix) {
	vec4 lVector = mul(vec4(aVector, 1.0f), aMatrix);
	return lVector.xyz / lVector.w;
}

float Clamp(float aValue, float aMin, float aMax) {
	if(aValue < aMin) aValue = aMin;
	if(aValue > aMax) aValue = aMax;
	return aValue;
}

vec4 Clamp(vec4 aVector, float aMin, float aMax) {
	return vec4(
		Clamp(aVector.x, aMin, aMax),
		Clamp(aVector.y, aMin, aMax),
		Clamp(aVector.z, aMin, aMax),
		Clamp(aVector.w, aMin, aMax)
	);
}


float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float SpecularPhong(vec3 aToView, vec3 aNor, vec3 aToLight, int aSpecularPow) {
	vec3 halfVector = normalize(aToView + aToLight);
	float specular = pow(max(dot(aNor, halfVector), 0.0f), int(aSpecularPow));
	return specular;
}

vec3 GetBampNormalTan(vec2 aTexCoord) {
	vec3 lBampNormalTan = texture(BampTexture, vec2(aTexCoord.x, 1.0f - aTexCoord.y)).xyz * 2.0f - 1.0f;
	lBampNormalTan.xy *= -1.0f;	//�E��n���W���獶��n���W�ւ̕ϊ�
	return lBampNormalTan;
}



void main() {

	//�^���W�F���g��Ԃł̖@���x�N�g���̎擾
	vec3 bampNormalTan = GetBampNormalTan(InTexCoord);

	//�f�B�t���[�Y�̌v�Z
	//
	vec4 diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuse *= Diffuse;
	vec4 diffuseTexel = texture(DiffuseTexture, vec2(InTexCoord.x, 1.0f - InTexCoord.y));
	diffuse *= diffuseTexel;	//�f�B�t���[�Y�e�N�X�`���̓K�p
	float diffuseLighting = Lambert(bampNormalTan, normalize(InToLightTan));
	diffuse.xyz *= diffuseLighting;

	//�X�y�L�����[�̌v�Z
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	//specular *= Specular;
	float specularLighting = SpecularPhong(normalize(InToCameraTan), bampNormalTan, normalize(InToLightTan), 20);
	specular *= specularLighting;

	vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	color += diffuse;
	color += vec4(specular.xyz, 0.0f);

	color.a = min(color.a, 1.0f);

	OutColor = Clamp(color, 0.0f, 1.0f);
}
