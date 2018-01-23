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
	float3 CameraPosition;
	float _Dummy1;
	float Timer;
};


Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);


struct VS_INPUT {
	float3 Pos : POSITION;   // ���_���W(���f�����W�n)
	float3 Nor : NORMAL;	// �@���x�N�g��(���f�����W�n)
	float2 Tex : TEXTURE;	//�e�N�X�`�����W
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

float3 Mul(float3 aVector, matrix aMatrix) {
	float4 lVector = mul(float4(aVector, 1.0f), aMatrix);
	return lVector.xyz / lVector.w;
}