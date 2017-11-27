// 定数バッファのデータ定義
cbuffer cWVPBuffer : register(b0) { // 常にスロット「0」を使う
	matrix View;   // ビュー変換行列
	matrix Projection;   // 透視変換行列
	matrix World;      // ワールド変換行列
	matrix NorWorld;      // ワールド変換行列
};
// 定数バッファのデータ定義
cbuffer cDiffuseBuffer : register(b1) { // 常にスロット「0」を使う
	float4 Diffuse;
};
cbuffer cTimerBuffer : register(b2) { // 常にスロット「0」を使う
	float Timer;
};


Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float3 Nor : NORMAL;	// 法線ベクトル(モデル座標系)
	float2 Tex : TEXTURE;	//テクスチャ座標
};

struct PS_PHONG_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float4 PosWor	: POS_WOR; //頂点座標（ワールド）
	float4 NorWor	: NORMAL;	//法線ベクトル（ワールド）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


VS_INPUT VS_TEST(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// ジオメトリ シェーダの関数
[maxvertexcount(3)]
void GS_TEST(triangle VS_INPUT input[3],
	inout TriangleStream<PS_PHONG_INPUT> TriStream) {

	PS_PHONG_INPUT output;

	for (int i = 0; i < 3; ++i) {

		output.PosWor = mul(float4(input[i].Pos, 1.0f), World);

		output.PosProj = mul(output.PosWor, View);
		output.PosProj = mul(output.PosProj, Projection);

		output.NorWor = mul(float4(input[i].Nor, 1.0f), NorWorld);

		output.Tex = input[i].Tex;

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}

float4 PS_TEST(PS_PHONG_INPUT input) : SV_TARGET{

	float4 col = Diffuse;

	float4 texel = myTexture.Sample(mySampler, input.Tex);
	col *= texel;

	return col;
}
