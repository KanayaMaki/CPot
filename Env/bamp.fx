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
	float3 ToLightTan : TOLIGHT_TAN;	//���ւ̃x�N�g���i�^���W�F���g�j
	float3 ToCameraTan : TOCAMERA_TAN;	//���_�ւ̃x�N�g���i�^���W�F���g�j
	float2 Tex	: TEXTURE;	//�e�N�X�`�����W
};


VS_BAMP_INPUT VS_MAIN(VS_BAMP_INPUT input) {
	VS_BAMP_INPUT output;
	output = input;
	return output;
}


float3 TransformToTangentSpace(float3 aVec, float3 aNormal, float3 aTangent, float3 aBiNormal) {

	matrix lTanToLoc = matrix(
		float4(aTangent.x, aTangent.y, aTangent.z, 0.0f),
		float4(aBiNormal.x, aBiNormal.y, aBiNormal.z, 0.0f),
		float4(aNormal.x, aNormal.y, aNormal.z, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	matrix lLocToTan = transpose(lTanToLoc);

	float3 lVecTan = Mul(aVec, lLocToTan);

	return lVecTan;
}

float3 GetBampNormalTan(Texture2D lBampTexture, SamplerState lBampSampler, float2 aTexCoord) {
	float3 lBampNormalTan = lBampTexture.Sample(lBampSampler, aTexCoord).xyz * 2.0f - 1.0f;
	lBampNormalTan.xy *= -1.0f;	//�E��n���W���獶��n���W�ւ̕ϊ�
	return lBampNormalTan;
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

		output.ToLightTan = TransformToTangentSpace(ToLight, input[i].Nor, input[i].Tan, input[i].BiNor);

		float3 lToCamera = CameraPositionLoc - input[i].Pos;
		output.ToCameraTan = TransformToTangentSpace(normalize(lToCamera), input[i].Nor, input[i].Tan, input[i].BiNor);

		output.Tex = input[i].Tex;

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	//�^���W�F���g��Ԃł̖@���x�N�g���̎擾
	float3 bampNormalTan = GetBampNormalTan(BampTexture, BampSampler, input.Tex);
	
	//
	//�f�B�t���[�Y�̌v�Z
	float4 diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuse *= Diffuse;	//�}�e���A���F�̓K�p
	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	diffuse *= diffuseTexel;	//�e�N�X�`���̓K�p
	float diffuseLighting = Lambert(bampNormalTan, normalize(input.ToLightTan));
	diffuse.xyz *= diffuseLighting;	//���C�e�B���O�̓K�p
	
	//
	//�X�y�L�����[�̌v�Z
	float3 specular = float3(1.0f, 1.0f, 1.0f);
	//specular.xyz *= Specular;	//�X�y�L�����F�̓K�p
	float specularLighting = SpecularPhong(normalize(input.ToCameraTan), bampNormalTan, normalize(input.ToLightTan), 20);
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
