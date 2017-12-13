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
	float Timer;
};


Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);


struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float3 Nor : NORMAL;	// 法線ベクトル(モデル座標系)
	float2 Tex : TEXTURE;	//テクスチャ座標
};
