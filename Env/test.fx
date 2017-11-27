// �萔�o�b�t�@�̃f�[�^��`
cbuffer cWVPBuffer : register(b0) { // ��ɃX���b�g�u0�v���g��
	matrix View;   // �r���[�ϊ��s��
	matrix Projection;   // �����ϊ��s��
	matrix World;      // ���[���h�ϊ��s��
	matrix NorWorld;      // ���[���h�ϊ��s��
};
// �萔�o�b�t�@�̃f�[�^��`
cbuffer cDiffuseBuffer : register(b1) { // ��ɃX���b�g�u0�v���g��
	float4 Diffuse;
};
cbuffer cTimerBuffer : register(b2) { // ��ɃX���b�g�u0�v���g��
	float Timer;
};


Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct VS_INPUT {
	float3 Pos : POSITION;   // ���_���W(���f�����W�n)
	float3 Nor : NORMAL;	// �@���x�N�g��(���f�����W�n)
	float2 Tex : TEXTURE;	//�e�N�X�`�����W
};

struct PS_PHONG_INPUT {
	float4 PosProj	: SV_POSITION; //���_���W�i�v���W�F�N�V�����j
	float4 PosWor	: POS_WOR; //���_���W�i���[���h�j
	float4 NorWor	: NORMAL;	//�@���x�N�g���i���[���h�j
	float2 Tex	: TEXTURE;	//�e�N�X�`�����W
};


VS_INPUT VS_TEST(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// �W�I���g�� �V�F�[�_�̊֐�
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
