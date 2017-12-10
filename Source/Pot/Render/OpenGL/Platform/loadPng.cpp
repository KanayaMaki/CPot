#include "readpng.h"

using namespace kolib;

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Chank {
	std::string type;
	s32 length;
	std::string data;
};

s32 Endian(s32 e) {
	s32 a = 0;
	char* eA = (char*)&e;
	char* aA = (char*)&a;
	for (s32 i = 0; i < 4; i++) {
		aA[i] = eA[3 - i];
	}
	return a;
}

s32 BuildIndex(s32 lineWidthBytes, s32 y, s32 x, s32 pixelBytes) {
	return lineWidthBytes * y + x * pixelBytes + 1;
}

const s32 kOutBufSize = 1024;
char outBuf[kOutBufSize];

PNGData LoadPNGFromFile(const kolib::CHAR* fileName) {
	std::vector<Chank*> v;
	std::ifstream file(fileName, std::ios::binary);
	file.seekg(8, std::ios::cur);

	while (!file.eof()) {
		s32 f = file.tellg();
		Chank* c = new Chank;
		v.push_back(c);
		char buffer[1000000];
		file.read(buffer, 4);
		c->length = *(s32*)buffer;
		c->length = Endian(c->length);
		file.read(buffer, 4);
		c->type.append(buffer, 4);
		f = file.tellg();
		if (c->type == "IHDR") {
			file.read(buffer, c->length);
			c->data.append(buffer, c->length);
		}
		else if (c->type == "IDAT") {
			file.read(buffer, c->length);
			c->data.append(buffer, c->length);
		}
		else if (c->type == "IEND") {
			break;
		}
		else {
			file.read(buffer, c->length);
			c->data.append(buffer, c->length);
		}
		file.read(buffer, 4);
	}

	s32 width = Endian(*(s32*)(&(v[0]->data.c_str()[0])));
	s32 height = Endian(*(s32*)(&(v[0]->data.c_str()[4])));
	s32 depth = v[0]->data.c_str()[8];
	s32 colorType = v[0]->data.c_str()[9];
	s32 compFormat = v[0]->data.c_str()[10];
	s32 filterFormat = v[0]->data.c_str()[11];
	s32 interraceFormat = v[0]->data.c_str()[12];

	z_stream z;
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;

	z.next_in = Z_NULL;
	z.avail_in = 0;

	s32 result = inflateInit(&z);

	std::string pngData;
	std::for_each(v.begin(), v.end(), 
		[&](Chank* c){
		if (c->type == "IDAT") {
			s32 status, count;
			z.next_out = (Bytef*)outBuf;
			z.avail_out = kOutBufSize;
			status = Z_OK;
			z.next_in = (Bytef*)(c->data.c_str());
			z.avail_in = c->data.length();

			while (status != Z_STREAM_END) {
				status = inflate(&z, Z_NO_FLUSH);
				if (status == Z_STREAM_END) break;
				if (z.avail_in == 0) {
					break;
				}
				if (status != Z_OK) {
					abort();
				}
				if (z.avail_out == 0) {
					pngData.append(outBuf, kOutBufSize);
					z.next_out = (Bytef*)outBuf;
					z.avail_out = kOutBufSize;
				}
			}
			if ((count = kOutBufSize - z.avail_out) != 0) {
				pngData.append(outBuf, count);
			}
		}
	});

	inflateEnd(&z);

	s32 pixelSize;
	switch (colorType) {
		case 0:
			pixelSize = 1 * depth / 8;
			break;
		case 2:
			pixelSize = 3 * depth / 8;
			break;
		case 4:
			pixelSize = 2 * depth / 8;
			break;
		case 6:
			pixelSize = 4 * depth / 8;
			break;
	}

	s32 widthSize = pixelSize * width + 1;

	/*
	for (s32 i = height - 1; i >= 0; i--) {
		s32 type = pngData[i * widthSize];
		switch (type) {
			case 0:
				break;
			case 1:
				for (s32 j = width - 1; j >= 0; j--) {
					for (s32 k = 0; k < pixelSize; k++) {
						s32 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						s32 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + leftCol) % 256;
					}
				}
				break;
			case 2:
				for (s32 j = width - 1; j >= 0; j--) {
					for (s32 k = 0; k < pixelSize; k++) {
						s32 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						s32 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + upCol) % 256;
					}
				}
				break;
			case 3:
				for (s32 j = width - 1; j >= 0; j--) {
					for (s32 k = 0; k < pixelSize; k++) {
						s32 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						s32 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						s32 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + (upCol + leftCol) / 2) % 256;
					}
				}
				break;

			case 4:
				for (s32 j = width - 1; j >= 0; j--) {
					for (s32 k = 0; k < pixelSize; k++) {
						s32 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						s32 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						s32 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						s32 leftUpCol;
						if (j == 0 || i == 0) leftUpCol = 0;
						else leftUpCol = pngData[BuildIndex(widthSize, i - 1, j - 1, pixelSize) + k];

						s32 x = leftCol + upCol - leftUpCol;
						s32 a = Abs(x - leftCol);
						s32 b = Abs(x - upCol);
						s32 c = Abs(x - leftUpCol);
						s32 min = Min(a, Min(b, c));

						s32 col;
						if (min == a) col = leftCol;
						else if (min == b) col = upCol;
						else if (min == c) col = leftUpCol;

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + col) % 256;
					}
				}
				break;
		}
	}
	//*/

	///*
	for (s32 i = 0; i < height; i++) {
		s32 type = pngData[i * widthSize];
		switch (type) {
			case 0:
				break;
			case 1:
				for (s32 j = 0; j < width; j++) {
					for (s32 k = 0; k < pixelSize; k++) {
						u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						u8 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + leftCol) % 256;
					}
				}
				break;
			case 2:
				for (s32 j = 0; j < width; j++) {
					for (s32 k = 0; k < pixelSize; k++) {
						u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						u8 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + upCol) % 256;
					}
				}
				break;
			case 3:
				for (s32 j = 0; j < width; j++) {
					for (s32 k = 0; k < pixelSize; k++) {
						u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						u8 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						u8 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + (upCol + leftCol) / 2) % 256;
					}
				}
				break;

			case 4:
				for (s32 j = 0; j < width; j++) {
					for (s32 k = 0; k < pixelSize; k++) {
						u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
						u8 upCol;
						if (i == 0) upCol = 0;
						else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

						u8 leftCol;
						if (j == 0) leftCol = 0;
						else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

						u8 leftUpCol;
						if (j == 0 || i == 0) leftUpCol = 0;
						else leftUpCol = pngData[BuildIndex(widthSize, i - 1, j - 1, pixelSize) + k];

						s32 x = leftCol + upCol - leftUpCol;
						s32 a = Abs(x - leftCol);
						s32 b = Abs(x - upCol);
						s32 c = Abs(x - leftUpCol);
						s32 min = Min(a, Min(b, c));

						u8 col;
						if (min == a) col = leftCol;
						else if (min == b) col = upCol;
						else if (min == c) col = leftUpCol;

						pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + col) % 256;
					}
				}
				break;
		}
	}
	//*/

	PNGData a;
	a.height = height;
	a.width = width;
	a.depth = depth;
	a.pixelBytes = pixelSize;

	for (s32 i = 0; i < height; i++) {
		s32 start = BuildIndex(widthSize, i, 0, pixelSize);
		s32 end = BuildIndex(widthSize, i + 1, 0, pixelSize) - 1;
		a.data.append(&(pngData[start]), &(pngData[end]));
	}

	return a;
}