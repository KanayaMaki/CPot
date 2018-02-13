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
	float3 ToLightTan : TOLIGHT_TAN;	//光へのベクトル（タンジェント）
	float3 ToCameraTan : TOCAMERA_TAN;	//視点へのベクトル（タンジェント）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};

float3 TransformToTangentSpace(float3 aVec, float3 aNormal, float3 aTangent, float3 aBiNormal) {

	matrix lTanToLoc = CreateMatrixP(aTangent, aBiNormal, aNormal);
	matrix lLocToTan = transpose(lTanToLoc);

	float3 lVecTan = MultiP(aVec, lLocToTan);

	return lVecTan;
}

float3 GetBampNormalTan(float2 aTexCoord) {
	float3 lBampNormalTan = BampTexture.Sample(BampSampler, float2(aTexCoord.x, aTexCoord.y)).xyz * 2.0f - 1.0f;
	lBampNormalTan.xy *= -1.0f;	//右手系座標から左手系座標への変換
	return lBampNormalTan;
}


PS_INPUT VS_MAIN(VS_BAMP_INPUT input) {

	PS_INPUT output;

	//ワールド座標での位置
	float4 lPosWor = MultiP(float4(input.Pos, 1.0f), World);
	output.PosWor = lPosWor.xyz / lPosWor.w;

	//プロジェクション座標での位置
	float4 lPosView = MultiP(lPosWor, View);
	float4 lPosProj = MultiP(lPosView, Projection);
	output.PosProj = lPosProj;

	output.ToLightTan = TransformToTangentSpace(ToLight, input.Nor, input.Tan, input.BiNor);

	float3 lToCamera = CameraPositionLoc - input.Pos;
	output.ToCameraTan = TransformToTangentSpace(normalize(lToCamera), input.Nor, input.Tan, input.BiNor);

	output.Tex = input.Tex;

	return output;
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	//タンジェント空間での法線ベクトルの取得
	float3 bampNormalTan = GetBampNormalTan(input.Tex);

	//
	//ディフューズの計算
	float4 diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuse *= Diffuse;	//マテリアル色の適用
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, float2(input.Tex.x, input.Tex.y));
	diffuse *= diffuseTexel;	//テクスチャの適用
	float diffuseLighting = Lambert(bampNormalTan, normalize(input.ToLightTan));
	diffuse.xyz *= diffuseLighting;	//ライティングの適用

	//
	//スペキュラーの計算
	float3 specular = float3(1.0f, 1.0f, 1.0f);
	//specular.xyz *= Specular;	//スペキュラ色の適用
	float specularLighting = SpecularPhong(normalize(input.ToCameraTan), bampNormalTan, normalize(input.ToLightTan), 20);
	specular *= specularLighting;	//ライティングの適用

	//計算した色を足し合わせる
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color += diffuse;
	color += float4(specular.xyz, 0.0f);

	//アルファは1.0を超えない
	color.a = min(color.a, 1.0f);

	output.Diffuse = color;

	return output;
}
