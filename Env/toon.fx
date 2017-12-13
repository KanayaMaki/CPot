#include "./union.fx"

Texture2D ToonTexture : register(t1);
SamplerState ToonSampler : register(s1);


struct PS_PHONG_INPUT {
	float4 PosProj	: SV_POSITION; //���_���W�i�v���W�F�N�V�����j
	float4 PosWor	: POS_WOR; //���_���W�i���[���h�j
	float4 NorWor	: NORMAL;	//�@���x�N�g���i���[���h�j
	float2 Tex	: TEXTURE;	//�e�N�X�`�����W
};


VS_INPUT VS_MAIN(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// �W�I���g�� �V�F�[�_�̊֐�
[maxvertexcount(3)]
void GS_MAIN(triangle VS_INPUT input[3],
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


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


float Lambert(float3 aNormal, float3 aToLight) {
	float3 normalN = normalize(aNormal);
	float3 toLightN = normalize(-LightDirection);

	float lambert = dot(toLightN, normalN);
	return lambert;
}

float HalfLambert(float3 aNormal, float3 aToLight) {
	float lambert = Lambert(aNormal, aToLight);
	float halfLambert = pow((lambert * 0.5f + 0.5f), 2);
	return halfLambert;
}

PS_OUTPUT PS_MAIN(PS_PHONG_INPUT input) {

	PS_OUTPUT output;

	float lighting = HalfLambert(input.NorWor.xyz / input.NorWor.w , -LightDirection);
	float4 toonTexel = ToonTexture.Sample(ToonSampler, float2(lighting, lighting));

	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	color.xyz *= toonTexel;
	output.Diffuse = color;

	return output;
}
