#include "./union.fx"

struct PS_PHONG_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float4 PosWor	: POS_WOR; //頂点座標（ワールド）
	float4 NorWor	: NORMAL;	//法線ベクトル（ワールド）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


PS_PHONG_INPUT VS_MAIN(VS_INPUT input) {
	PS_PHONG_INPUT output;

	output.PosWor = MultiP(float4(input.Pos, 1.0f), World);

	output.PosProj = MultiP(output.PosWor, View);
	output.PosProj = MultiP(output.PosProj, Projection);

	output.NorWor = MultiP(float4(input.Nor, 1.0f), NorWorld);

	output.Tex = input.Tex;

	return output;
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};



PS_OUTPUT PS_MAIN(PS_PHONG_INPUT input) {

	PS_OUTPUT output;

	float lighting = HalfLambert(input.NorWor.xyz / input.NorWor.w , -LightDirection);
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, float2(input.Tex.x, input.Tex.y));

	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	color.xyz *= lighting;
	output.Diffuse = color;

	return output;
}
