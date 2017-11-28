// 定数バッファのデータ定義
cbuffer cWVPBuffer : register(b0) { // 常にスロット「0」を使う
	matrix View;   // ビュー変換行列
	matrix Projection;   // 透視変換行列
	matrix World;      // ワールド変換行列
	matrix NorWorld;      // ワールド変換行列
};
// 定数バッファのデータ定義
cbuffer cDiffuseBuffer : register(b1) { // 常にスロット「0」を使う
	float4 Diffuse;
};
cbuffer cTimerBuffer : register(b2) { // 常にスロット「0」を使う
	float Timer;
};


Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float3 Nor : NORMAL;	// 法線ベクトル(モデル座標系)
	float2 Tex : TEXTURE;	//テクスチャ座標
};

struct PS_PHONG_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float4 PosWor	: POS_WOR; //頂点座標（ワールド）
	float4 NorWor	: NORMAL;	//法線ベクトル（ワールド）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


VS_INPUT VS_TEST(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// ジオメトリ シェーダの関数
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


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};







//グレースケール化する関数
float4 ToGray(float4 col) {
	float l = col.r * 0.298912f + col.g * 0.586611f + col.b * 0.114478f;
	return float4(l, l, l, col.a);
}

//セピア化する関数
float4 ToSepiar(float4 col) {
	float4 res = ToGray(col);
	res.r *= (240.0f / 255.0f);
	res.g *= (200.0f / 255.0f);
	res.b *= (140.0f / 255.0f);
	return res;
}


//パーリンノイズのフェード
float Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

int XorShift32(int aV) {
	int tV = (int)aV;

	tV = tV ^ (tV << 13);
	tV = tV ^ (tV >> 17);
	tV = tV ^ (tV << 15);

	return (int)tV;
}


static const int p[512] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};



int Hash(int aV) {
	return XorShift32(aV);

	aV = aV % 256;
	return p[p[p[aV] + aV] + aV];
	//return aV;
}

float GetGradAxis(int aX, int aY, int aElem, int aSeed) {
	int r = Hash(aX + aSeed);
	r = Hash(r + aY);
	r = Hash(r + aElem) % 100000;
	return (float)r / 50000 - 1.0f;
}

float2 GetGrad(int aX, int aY, int aSeed) {
	return float2(GetGradAxis(aX, aY, 0, aSeed), GetGradAxis(aX, aY, 1, aSeed));
}
float2 GetGrad(int aX, int aY) {
	return GetGrad(aX, aY, 0);
}
float2 GetDist(float aX, float aY) {
	return float2(aX, aY);
}

//線形補間
float Lerp(float a, float b, float t) {
	return a + t * (b - a);
}
float2 Lerp(float2 a, float2 b, float t) {
	return a + t * (b - a);
}

//パーリンノイズを生成する関数
float Perlin(float x, float y) {

	int xi = (int)x;
	int yi = (int)y;

	float xf = x - (int)x;
	float yf = y - (int)y;

	float u = Fade(xf);
	float v = Fade(yf);

	//点を囲む四角形の頂点の、勾配を取得
	float2 aa, ab, ba, bb;
	aa = GetGrad(xi, yi);
	ab = GetGrad(xi, yi + 1);
	ba = GetGrad(xi + 1, yi);
	bb = GetGrad(xi + 1, yi + 1);

	float daa, dab, dba, dbb;
	daa = dot(aa, GetDist(xf, yf));
	dab = dot(ab, GetDist(xf, yf - 1.0f));
	dba = dot(ba, GetDist(xf - 1.0f, yf));
	dbb = dot(bb, GetDist(xf - 1.0f, yf - 1.0f));

	float res = Lerp(Lerp(daa, dab, v), Lerp(dba, dbb, v), u);
	return (res + 1.0f) / 2.0f;
}

float OctavePerlin(float x, float y, int octaves, float persistence) {

	float total = 0.0f;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	float maxValue = 0.0f;

	for (int i = 0; i < octaves; i++) {
		total += Perlin(x * frequency, y * frequency) * amplitude;
		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}




PS_OUTPUT PS_TEST(PS_PHONG_INPUT input) {

	PS_OUTPUT output;

	float4 col = Diffuse;

	float4 texel = myTexture.Sample(mySampler, input.Tex);
	col *= texel;

	//col *= Timer;
	col *= OctavePerlin(input.Tex.x * 5.0f, input.Tex.y * 5.0f, 5, 0.8f);

	output.Diffuse = col;

	return output;
}
