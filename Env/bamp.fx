#include "./union.fx"

Texture2D BampTexture : register(t1);
SamplerState BampSampler : register(s1);


struct VS_BAMP_INPUT {
	float3 Pos : POSITION;   // ���_���W(���f�����W�n)
	float3 Nor : NORMAL;	// �@���x�N�g��(���f�����W�n)
	float3 Tan : TANGENT;	// �ڐ��x�N�g��(���f�����W�n)
	float3 BiNor : BINORMAL;	// �]�@���x�N�g��(���f�����W�n)
	float2 Tex : TEXTURE;	//�e�N�X�`�����W
};

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //���_���W�i�v���W�F�N�V�����j
	float3 PosWor	: POS_WOR; //���_���W�i���[���h�j
	float3 NorWor	: NORMAL;	//�@���x�N�g���i���[���h�j
	float3 TanWor	: TANGENT;	//�ڐ��x�N�g���i���[���h�j
	float3 BiNorWor	: BINORMAL;	//�]�@���x�N�g���i���[���h�j
	float2 Tex	: TEXTURE;	//�e�N�X�`�����W
};


VS_BAMP_INPUT VS_MAIN(VS_BAMP_INPUT input) {
	VS_BAMP_INPUT output;
	output = input;
	return output;
}

// �W�I���g�� �V�F�[�_�̊֐�
[maxvertexcount(3)]
void GS_MAIN(triangle VS_BAMP_INPUT input[3],
	inout TriangleStream<PS_INPUT> TriStream) {

	PS_INPUT output;

	for (int i = 0; i < 3; ++i) {
		
		//���[���h���W�ł̈ʒu
		float4 lPosWor = mul(float4(input[i].Pos, 1.0f), World);
		output.PosWor = lPosWor.xyz / lPosWor.w;

		//�v���W�F�N�V�������W�ł̈ʒu
		float4 lPosView = mul(lPosWor, View);
		float4 lPosProj = mul(lPosView, Projection);
		output.PosProj = lPosProj;

		//���[���h���W�ł̖@��
		float4 lNorWor = mul(float4(input[i].Nor, 1.0f), NorWorld);
		output.NorWor = lNorWor.xyz / lNorWor.w;

		//���[���h���W�ł̐ڐ�
		float4 lTanWor = mul(float4(input[i].Tan, 1.0f), NorWorld);
		output.TanWor = lTanWor.xyz / lTanWor.w;

		//���[���h���W�ł̏]�@��
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

	//�o���v��K�p�������@���̎擾
	float3 bampNormalWor = BampNormal(input.Tex, normalize(input.NorWor), normalize(input.TanWor), normalize(input.BiNorWor));
	float lighting = Lambert(bampNormalWor, -LightDirection);

	//�e�N�X�`��
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;	//�}�e���A���F�̓K�p
	color *= diffuseTexel;	//�e�N�X�`���̓K�p
	color.xyz *= lighting;	//���C�e�B���O�̓K�p
	
	output.Diffuse = color;

	return output;
}
