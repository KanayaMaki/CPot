#include "./union.fx"

cbuffer cToonLineBuffer : register(b3) { // 常にスロット「0」を使う
	float LineWidth;	//頂点を法線方向に伸ばす長さ
};

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
};


VS_INPUT VS_MAIN(VS_INPUT input) {
	PS_INPUT output;

	float3 lModelPos = input.Pos + input.Nor * LineWidth;

	float4 lWorldPos = MultiP(float4(lModelPos, 1.0f), World);

	float4 lViewPos = MultiP(lWorldPos, View);
	output.PosProj = MultiP(lViewPos, Projection);

	return output;
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;
	output.Diffuse = Diffuse;

	return output;
}
