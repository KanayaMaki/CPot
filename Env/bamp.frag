#version 430 core

layout(location = 0) in vec3 InPosWor;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec3 InTanLoc;
layout(location = 3) in vec3 InBiNorLoc;
layout(location = 4) in vec2 InTexCoord;

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
    float Timer;
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

float Lambert(vec3 aNormal, vec3 aToLight) {
	vec3 normalN = normalize(aNormal);
	vec3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float SpecularPhong(vec3 aToViewWor, vec3 aNorWor, vec3 aToLightWor, int aSpecularPow) {
	vec3 refToView = -aToViewWor + 2.0f * dot(aNorWor, aToViewWor) * aNorWor;
	float specular = pow(max(dot(refToView, normalize(aToLightWor)), 0), aSpecularPow);
	return specular;
}

vec3 BampNormal(vec2 aTexCoord, vec3 aNormal, vec3 aTangent, vec3 aBiNormal) {
	vec3 lBampNormalTan = texture(BampTexture, vec2(aTexCoord.x, 1.0f - aTexCoord.y)).xyz * 2.0f - 1.0f;
	lBampNormalTan.xy = -lBampNormalTan.xy;

	mat4x4 lTanToLoc = mat4x4(
		vec4(aTangent.x, aTangent.y, aTangent.z, 0.0f),
		vec4(aBiNormal.x, aBiNormal.y, aBiNormal.z, 0.0f),
		vec4(aNormal.x, aNormal.y, aNormal.z, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	lTanToLoc = transpose(lTanToLoc);

	vec3 lBampNor = mul(lBampNormalTan, lTanToLoc);

	return lBampNor;
}



void main() {

	//バンプを適用させた法線の取得
	vec3 bampNormalLoc = BampNormal(InTexCoord, normalize(InNorLoc), normalize(InTanLoc), normalize(InBiNorLoc));
	vec3 bampNormalWor = mul(normalize(bampNormalLoc), NorWorld);
	
	
	//ディフューズの計算
	vec4 diffuse = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuse *= Diffuse;
	vec4 diffuseTexel = texture(DiffuseTexture, vec2(InTexCoord.x, 1.0f - InTexCoord.y));
	diffuse *= diffuseTexel;	//ディフューズテクスチャの適用
	float diffuseLighting = Lambert(bampNormalWor, -LightDirection);
	diffuse.xyz *= diffuseLighting;

	//スペキュラーの計算
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	//specular *= Specular;
	float specularLighting = SpecularPhong(normalize(CameraPosition - InPosWor), bampNormalWor, normalize(-LightDirection), 250);
	specular *= specularLighting;

	vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	color += diffuse;
	color += vec4(specular.xyz, 0.0f);

	color.a = min(color.a, 1.0f);

	OutColor = color;
}