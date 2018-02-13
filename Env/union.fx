// 定数バッファのデータ定義
cbuffer cWVPBuffer : register(b0) { // 常にスロット「0」を使う
	matrix World;      // ワールド変換行列
	matrix View;   // ビュー変換行列
	matrix Projection;   // 透視変換行列
	matrix NorWorld;      // ワールド変換行列
};
// 定数バッファのデータ定義
cbuffer cDiffuseBuffer : register(b1) { // 常にスロット「0」を使う
	float4 Diffuse;
};
cbuffer cTimerBuffer : register(b2) { // 常にスロット「0」を使う
	float3 LightDirection;
	float _Dummy0;
	float3 CameraPosition;
	float _Dummy1;
	float3 ToLight;	//ライトへのベクトル（ローカル）
	float _Dummy3;
	float3 CameraPositionLoc;	//カメラ座標（ローカル）
	float _Dummy4;
};


Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);


struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float3 Nor : NORMAL;	// 法線ベクトル(モデル座標系)
	float2 Tex : TEXTURE;	//テクスチャ座標
};


//<HLSLRegion>
float4 MultiP(float4 aVector, matrix aMatrix) {
	return mul(aVector, aMatrix);
}

//三軸で示される空間から、三軸が存在する空間に移動する行列を作成
matrix CreateMatrixP(float3 aVecX, float3 aVecY, float3 aVecZ) {
	matrix lMatrix = matrix(
		float4(aVecX.x, aVecX.y, aVecX.z, 0.0f),
		float4(aVecY.x, aVecY.y, aVecY.z, 0.0f),
		float4(aVecZ.x, aVecZ.y, aVecZ.z, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	return lMatrix;
}

//</HLSLRegion>

/*<GLSLRegion>
vec4 MultiP(vec4 aVector, mat4x4 aMatrix) {
	return aVector * aMatrix;
}
mat4x4 CreateMatrixP(vec3 aVecX, vec3 aVecY, vec3 aVecZ) {
	matrix lMatrix = matrix(
		vec4(aVecX.x, aVecX.y, aVecX.z, 0.0),
		vec4(aVecY.x, aVecY.y, aVecY.z, 0.0),
		vec4(aVecZ.x, aVecZ.y, aVecZ.z, 0.0),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	return transpose(lMatrix);
}

*///</GLSLRegion>



float Lambert(float3 aNormal, float3 aToLight) {
	float3 normalN = normalize(aNormal);
	float3 toLightN = normalize(aToLight);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float HalfLambert(float3 aNormal, float3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	float halfLambert = pow((lambert * 0.5f + 0.5f), 2);
	return halfLambert;
}
float HalfLambert(float aLighting) {
	float halfLambert = pow((aLighting * 0.5f + 0.5f), 2);
	return halfLambert;
}

float3 MultiP(float3 aVector, matrix aMatrix) {
	float4 lVector = MultiP(float4(aVector, 1.0f), aMatrix);
	return lVector.xyz / lVector.w;
}

float SpecularPhong(float3 aToView, float3 aNor, float3 aToLight, int aSpecularPow) {
	float3 halfVector = normalize(aToView + aToLight);
	float specular = pow(max(dot(aNor, halfVector), 0.0f), int(aSpecularPow));
	return specular;
}
