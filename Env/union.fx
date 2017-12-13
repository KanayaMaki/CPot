// �萔�o�b�t�@�̃f�[�^��`
cbuffer cWVPBuffer : register(b0) { // ��ɃX���b�g�u0�v���g��
	matrix World;      // ���[���h�ϊ��s��
	matrix View;   // �r���[�ϊ��s��
	matrix Projection;   // �����ϊ��s��
	matrix NorWorld;      // ���[���h�ϊ��s��
};
// �萔�o�b�t�@�̃f�[�^��`
cbuffer cDiffuseBuffer : register(b1) { // ��ɃX���b�g�u0�v���g��
	float4 Diffuse;
};
cbuffer cTimerBuffer : register(b2) { // ��ɃX���b�g�u0�v���g��
	float3 LightDirection;
	float _Dummy0;
	float Timer;
};


Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);


struct VS_INPUT {
	float3 Pos : POSITION;   // ���_���W(���f�����W�n)
	float3 Nor : NORMAL;	// �@���x�N�g��(���f�����W�n)
	float2 Tex : TEXTURE;	//�e�N�X�`�����W
};
