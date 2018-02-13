#include "./union.fx"

Texture2D ToonTexture : register(t1);
SamplerState ToonSampler : register(s1);


struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float3 PosWor	: POS_WOR; //頂点座標（ワールド）
	float3 NorWor	: NORMAL;	//法線ベクトル（ワールド）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


PS_INPUT VS_MAIN(VS_INPUT input) {

	PS_INPUT output;

	float4 lPosWor = MultiP(float4(input.Pos, 1.0f), World);
	output.PosWor = lPosWor.xyz / lPosWor.w;

	float4 lPosView = MultiP(lPosWor, View);
	float4 lPosProj = MultiP(lPosView, Projection);
	output.PosProj = lPosProj;

	float4 lNorWor = MultiP(float4(input.Nor, 1.0f), NorWorld);
	output.NorWor = lNorWor.xyz / lNorWor.w;

	output.Tex = input.Tex;

	return output;
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	float lighting = HalfLambert(input.NorWor, -LightDirection);
	float4 toonTexel = ToonTexture.Sample(ToonSampler, float2(lighting, 1.0f - lighting));

	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, float2(input.Tex.x, input.Tex.y));

	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	color.xyz *= toonTexel.xyz;

	output.Diffuse = color;

	return output;
}
