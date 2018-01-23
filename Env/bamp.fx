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
	float3 Nor	: NORMAL;	//�@���x�N�g���i���f���j
	float3 Tan	: TANGENT;	//�ڐ��x�N�g���i���f���j
	float3 BiNor	: BINORMAL;	//�]�@���x�N�g���i���f���j
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

		output.Nor = input[i].Nor;
		output.BiNor = input[i].BiNor;
		output.Tan = input[i].Tan;

		output.Tex = input[i].Tex;

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};



float3 BampNormal(float2 aTexCoord, float3 aNormal, float3 aTangent, float3 aBiNormal) {

	float3 lBampNormalTan = BampTexture.Sample(BampSampler, aTexCoord).xyz * 2.0f - 1.0f;
	lBampNormalTan.xy = -lBampNormalTan.xy;
	
	matrix lTanToLoc = matrix(
		float4(aTangent.x, aTangent.y, aTangent.z, 0.0f),
		float4(aBiNormal.x, aBiNormal.y, aBiNormal.z, 0.0f),
		float4(aNormal.x, aNormal.y, aNormal.z, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
		);

	float3 lBampNor = Mul(lBampNormalTan, lTanToLoc);

	return lBampNor;
}



PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	//�o���v��K�p�������@���̎擾
	float3 bampNormal = BampNormal(input.Tex, normalize(input.Nor), normalize(input.Tan), normalize(input.BiNor));
	float3 bampNormalWor = Mul(normalize(bampNormal), NorWorld);
	
	//
	//�f�B�t���[�Y�̌v�Z
	float4 diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuse *= Diffuse;	//�}�e���A���F�̓K�p
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	diffuse *= diffuseTexel;	//�e�N�X�`���̓K�p
	float diffuseLighting = Lambert(bampNormalWor, -LightDirection);
	diffuse.xyz *= diffuseLighting;	//���C�e�B���O�̓K�p
	
	//
	//�X�y�L�����[�̌v�Z
	float3 specular = float3(1.0f, 1.0f, 1.0f);
	//specular.xyz *= Specular;	//�X�y�L�����F�̓K�p
	float specularLighting = SpecularPhong(normalize(CameraPosition - input.PosWor), bampNormalWor, normalize(-LightDirection), 250);
	specular *= specularLighting;	//���C�e�B���O�̓K�p

	//�v�Z�����F�𑫂����킹��
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color += diffuse;
	color += float4(specular.xyz, 0.0f);

	//�A���t�@��1.0�𒴂��Ȃ�
	color.a = min(color.a, 1.0f);

	output.Diffuse = color;

	return output;
}
