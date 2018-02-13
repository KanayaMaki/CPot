#include "./union.fx"

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


PS_INPUT VS_MAIN(VS_INPUT input) {

	PS_INPUT output;

	float4 lPosProj = MultiP(float4(input.Pos, 1.0f), World);
	lPosProj = MultiP(lPosProj, View);
	lPosProj = MultiP(lPosProj, Projection);

	output.PosProj = lPosProj;
	output.Tex = input.Tex;

	return output;
}

struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, float2(input.Tex.x, input.Tex.y));

	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	output.Diffuse = color;

	return output;
}
