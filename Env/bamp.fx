#include "./union.fx"

Texture2D BampTexture : register(t1);
SamplerState BampSampler : register(s1);


struct VS_BAMP_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float3 Nor : NORMAL;	// 法線ベクトル(モデル座標系)
	float3 Tan : TANGENT;	// 接線ベクトル(モデル座標系)
	float3 BiNor : BINORMAL;	// 従法線ベクトル(モデル座標系)
	float2 Tex : TEXTURE;	//テクスチャ座標
};

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float3 PosWor	: POS_WOR; //頂点座標（ワールド）
	float3 NorWor	: NORMAL;	//法線ベクトル（ワールド）
	float3 TanWor	: TANGENT;	//接線ベクトル（ワールド）
	float3 BiNorWor	: BINORMAL;	//従法線ベクトル（ワールド）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


VS_BAMP_INPUT VS_MAIN(VS_BAMP_INPUT input) {
	VS_BAMP_INPUT output;
	output = input;
	return output;
}

// ジオメトリ シェーダの関数
[maxvertexcount(3)]
void GS_MAIN(triangle VS_BAMP_INPUT input[3],
	inout TriangleStream<PS_INPUT> TriStream) {

	PS_INPUT output;

	for (int i = 0; i < 3; ++i) {
		
		//ワールド座標での位置
		float4 lPosWor = mul(float4(input[i].Pos, 1.0f), World);
		output.PosWor = lPosWor.xyz / lPosWor.w;

		//プロジェクション座標での位置
		float4 lPosView = mul(lPosWor, View);
		float4 lPosProj = mul(lPosView, Projection);
		output.PosProj = lPosProj;

		//ワールド座標での法線
		float4 lNorWor = mul(float4(input[i].Nor, 1.0f), NorWorld);
		output.NorWor = lNorWor.xyz / lNorWor.w;

		//ワールド座標での接線
		float4 lTanWor = mul(float4(input[i].Tan, 1.0f), NorWorld);
		output.TanWor = lTanWor.xyz / lTanWor.w;

		//ワールド座標での従法線
		float4 lBiNorWor = mul(float4(input[i].BiNor, 1.0f), NorWorld);
		output.BiNorWor = lBiNorWor.xyz / lBiNorWor.w;

		output.Tex = input[i].Tex;

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


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

float3 Transform(float3 aVector, matrix aMatrix) {
	float4 lVector = mul(float4(aVector, 1.0f), aMatrix);
	return lVector.xyz / lVector.w;
}

float3 BampNormal(float2 aTexCoord, float3 aNormalWor, float3 aTangentWor, float3 aBiNormalWor) {

	float3 lBampNormalTan = BampTexture.Sample(BampSampler, aTexCoord).xyz;
	lBampNormalTan.xy = lBampNormalTan.xy * 2.0f - 1.0f;

	matrix lTanToWor = matrix(
		float4(aTangentWor.x, aTangentWor.y, aTangentWor.z, 0.0f),
		float4(aBiNormalWor.x, aBiNormalWor.y, aBiNormalWor.z, 0.0f),
		float4(aNormalWor.x, aNormalWor.y, aNormalWor.z, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
		);

	float3 lBampNorWor = Transform(lBampNormalTan, lTanToWor);

	return normalize(lBampNorWor);
}



PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	//バンプを適用させた法線の取得
	float3 bampNormalWor = BampNormal(input.Tex, normalize(input.NorWor), normalize(input.TanWor), normalize(input.BiNorWor));
	float lighting = Lambert(bampNormalWor, -LightDirection);

	//テクスチャ
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;	//マテリアル色の適用
	color *= diffuseTexel;	//テクスチャの適用
	color.xyz *= lighting;	//ライティングの適用
	
	output.Diffuse = color;

	return output;
}
