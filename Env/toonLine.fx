#include "./union.fx"

cbuffer cToonLineBuffer : register(b3) { // ��ɃX���b�g�u0�v���g��
	float LineWidth;	//���_��@�������ɐL�΂�����
};

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //���_���W�i�v���W�F�N�V�����j
};


VS_INPUT VS_MAIN(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// �W�I���g�� �V�F�[�_�̊֐�
[maxvertexcount(3)]
void GS_MAIN(triangle VS_INPUT input[3],
	inout TriangleStream<PS_INPUT> TriStream) {

	PS_INPUT output;

	for (int i = 0; i < 3; ++i) {

		float3 lModelPos = input[i].Pos + input[i].Nor * LineWidth;

		float4 lWorldPos = mul(float4(lModelPos, 1.0f), World);

		float4 lViewPos = mul(lWorldPos, View);
		output.PosProj = mul(lViewPos, Projection);

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;
	output.Diffuse = Diffuse;

	return output;
}
