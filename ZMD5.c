/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef ZMD5_C_INCLUDED
#define ZMD5_C_INCLUDED

#include "ZMD5.h"

//#define ZMD5_MACRO_FUNCTIONS // These appear to be slightly slower!

static unsigned int rZMD5_Hash[4];
static unsigned int rZMD5_Counter[2];
static unsigned int rZMD5_Size[2];
static unsigned char rZMD5_Buffer[64];
static const unsigned char rZMD5_Padding[64] = {0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static char rZMD5_Digest[64]; // redundancy for alignment
#ifndef ZMD5_MACRO_FUNCTIONS
inline unsigned int ZMD5_R(unsigned int x, unsigned int n) {return (x << n) | (x >> (32 - n));}
inline unsigned int ZMD5_F(unsigned int x, unsigned int y, unsigned int z) {return ((x & y) | (~x & z));}
inline unsigned int ZMD5_G(unsigned int x, unsigned int y, unsigned int z) {return ((x & z) | (y & ~z));}
inline unsigned int ZMD5_H(unsigned int x, unsigned int y, unsigned int z) {return (x ^ y ^ z);}
inline unsigned int ZMD5_I(unsigned int x, unsigned int y, unsigned int z) {return (y ^ (x | ~z));}
inline void ZMD5_FF(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZMD5_R(*a + ZMD5_F(b, c, d) + x + ac, s) + b;}
inline void ZMD5_GG(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZMD5_R(*a + ZMD5_G(b, c, d) + x + ac, s) + b;}
inline void ZMD5_HH(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZMD5_R(*a + ZMD5_H(b, c ,d) + x + ac, s) + b;}
inline void ZMD5_II(unsigned int* a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {*a = ZMD5_R(*a + ZMD5_I(b, c, d) + x + ac, s) + b;}
#else
#define ZMD5_R(X,N) (((X) << (N)) | ((X) >> (32 - (N))))
#define ZMD5_F(X,Y,Z) (((X) & (Y)) | (~(X) & (Z)))
#define ZMD5_G(X,Y,Z) (((X) & (Z)) | ((Y) & ~(Z)))
#define ZMD5_H(X,Y,Z) ((X) ^ (Y) ^ (Z))
#define ZMD5_I(X,Y,Z) ((Y) ^ ((X) | ~(Z)))
#define ZMD5_FF(A,B,C,D,X,S,AC) (*(A) = ZMD5_R(*(A) + ZMD5_F((B), (C), (D)) + (X) + (AC), (S)) + (B))
#define ZMD5_GG(A,B,C,D,X,S,AC) (*(A) = ZMD5_R(*(A) + ZMD5_G((B), (C), (D)) + (X) + (AC), (S)) + (B))
#define ZMD5_HH(A,B,C,D,X,S,AC) (*(A) = ZMD5_R(*(A) + ZMD5_H((B), (C), (D)) + (X) + (AC), (S)) + (B))
#define ZMD5_II(A,B,C,D,X,S,AC) (*(A) = ZMD5_R(*(A) + ZMD5_I((B), (C), (D)) + (X) + (AC), (S)) + (B))
#endif // ZDM5_MACRO_FUNCTIONS
void ZMD5_Transform(const unsigned char* iInputBlock) {
    #define S11 7
    #define S12 12
    #define S13 17
    #define S14 22
    #define S21 5
    #define S22 9
    #define S23 14
    #define S24 20
    #define S31 4
    #define S32 11
    #define S33 16
    #define S34 23
    #define S41 6
    #define S42 10
    #define S43 15
    #define S44 21
	const unsigned int* x = (const unsigned int*)&iInputBlock[0];
	unsigned int a = rZMD5_Hash[0];
	unsigned int b = rZMD5_Hash[1];
	unsigned int c = rZMD5_Hash[2];
	unsigned int d = rZMD5_Hash[3];
	ZMD5_FF(&a, b, c, d, x[ 0], S11, 0xd76aa478); // 1
    ZMD5_FF(&d, a, b, c, x[ 1], S12, 0xe8c7b756); // 2
    ZMD5_FF(&c, d, a, b, x[ 2], S13, 0x242070db); // 3
    ZMD5_FF(&b, c, d, a, x[ 3], S14, 0xc1bdceee); // 4
    ZMD5_FF(&a, b, c, d, x[ 4], S11, 0xf57c0faf); // 5
    ZMD5_FF(&d, a, b, c, x[ 5], S12, 0x4787c62a); // 6
    ZMD5_FF(&c, d, a, b, x[ 6], S13, 0xa8304613); // 7
    ZMD5_FF(&b, c, d, a, x[ 7], S14, 0xfd469501); // 8
    ZMD5_FF(&a, b, c, d, x[ 8], S11, 0x698098d8); // 9
    ZMD5_FF(&d, a, b, c, x[ 9], S12, 0x8b44f7af); // 10
    ZMD5_FF(&c, d, a, b, x[10], S13, 0xffff5bb1); // 11
    ZMD5_FF(&b, c, d, a, x[11], S14, 0x895cd7be); // 12
    ZMD5_FF(&a, b, c, d, x[12], S11, 0x6b901122); // 13
    ZMD5_FF(&d, a, b, c, x[13], S12, 0xfd987193); // 14
    ZMD5_FF(&c, d, a, b, x[14], S13, 0xa679438e); // 15
    ZMD5_FF(&b, c, d, a, x[15], S14, 0x49b40821); // 16
    ZMD5_GG(&a, b, c, d, x[ 1], S21, 0xf61e2562); // 17
    ZMD5_GG(&d, a, b, c, x[ 6], S22, 0xc040b340); // 18
    ZMD5_GG(&c, d, a, b, x[11], S23, 0x265e5a51); // 19
    ZMD5_GG(&b, c, d, a, x[ 0], S24, 0xe9b6c7aa); // 20
    ZMD5_GG(&a, b, c, d, x[ 5], S21, 0xd62f105d); // 21
    ZMD5_GG(&d, a, b, c, x[10], S22,  0x2441453); // 22
    ZMD5_GG(&c, d, a, b, x[15], S23, 0xd8a1e681); // 23
    ZMD5_GG(&b, c, d, a, x[ 4], S24, 0xe7d3fbc8); // 24
    ZMD5_GG(&a, b, c, d, x[ 9], S21, 0x21e1cde6); // 25
    ZMD5_GG(&d, a, b, c, x[14], S22, 0xc33707d6); // 26
    ZMD5_GG(&c, d, a, b, x[ 3], S23, 0xf4d50d87); // 27
    ZMD5_GG(&b, c, d, a, x[ 8], S24, 0x455a14ed); // 28
    ZMD5_GG(&a, b, c, d, x[13], S21, 0xa9e3e905); // 29
    ZMD5_GG(&d, a, b, c, x[ 2], S22, 0xfcefa3f8); // 30
    ZMD5_GG(&c, d, a, b, x[ 7], S23, 0x676f02d9); // 31
    ZMD5_GG(&b, c, d, a, x[12], S24, 0x8d2a4c8a); // 32
    ZMD5_HH(&a, b, c, d, x[ 5], S31, 0xfffa3942); // 33
    ZMD5_HH(&d, a, b, c, x[ 8], S32, 0x8771f681); // 34
    ZMD5_HH(&c, d, a, b, x[11], S33, 0x6d9d6122); // 35
    ZMD5_HH(&b, c, d, a, x[14], S34, 0xfde5380c); // 36
    ZMD5_HH(&a, b, c, d, x[ 1], S31, 0xa4beea44); // 37
    ZMD5_HH(&d, a, b, c, x[ 4], S32, 0x4bdecfa9); // 38
    ZMD5_HH(&c, d, a, b, x[ 7], S33, 0xf6bb4b60); // 39
    ZMD5_HH(&b, c, d, a, x[10], S34, 0xbebfbc70); // 40
    ZMD5_HH(&a, b, c, d, x[13], S31, 0x289b7ec6); // 41
    ZMD5_HH(&d, a, b, c, x[ 0], S32, 0xeaa127fa); // 42
    ZMD5_HH(&c, d, a, b, x[ 3], S33, 0xd4ef3085); // 43
    ZMD5_HH(&b, c, d, a, x[ 6], S34,  0x4881d05); // 44
    ZMD5_HH(&a, b, c, d, x[ 9], S31, 0xd9d4d039); // 45
    ZMD5_HH(&d, a, b, c, x[12], S32, 0xe6db99e5); // 46
    ZMD5_HH(&c, d, a, b, x[15], S33, 0x1fa27cf8); // 47
    ZMD5_HH(&b, c, d, a, x[ 2], S34, 0xc4ac5665); // 48
    ZMD5_II(&a, b, c, d, x[ 0], S41, 0xf4292244); // 49
    ZMD5_II(&d, a, b, c, x[ 7], S42, 0x432aff97); // 50
    ZMD5_II(&c, d, a, b, x[14], S43, 0xab9423a7); // 51
    ZMD5_II(&b, c, d, a, x[ 5], S44, 0xfc93a039); // 52
    ZMD5_II(&a, b, c, d, x[12], S41, 0x655b59c3); // 53
    ZMD5_II(&d, a, b, c, x[ 3], S42, 0x8f0ccc92); // 54
    ZMD5_II(&c, d, a, b, x[10], S43, 0xffeff47d); // 55
    ZMD5_II(&b, c, d, a, x[ 1], S44, 0x85845dd1); // 56
    ZMD5_II(&a, b, c, d, x[ 8], S41, 0x6fa87e4f); // 57
    ZMD5_II(&d, a, b, c, x[15], S42, 0xfe2ce6e0); // 58
    ZMD5_II(&c, d, a, b, x[ 6], S43, 0xa3014314); // 59
    ZMD5_II(&b, c, d, a, x[13], S44, 0x4e0811a1); // 60
    ZMD5_II(&a, b, c, d, x[ 4], S41, 0xf7537e82); // 61
    ZMD5_II(&d, a, b, c, x[11], S42, 0xbd3af235); // 62
    ZMD5_II(&c, d, a, b, x[ 2], S43, 0x2ad7d2bb); // 63
    ZMD5_II(&b, c, d, a, x[ 9], S44, 0xeb86d391); // 64
	rZMD5_Hash[0] += a;
	rZMD5_Hash[1] += b;
	rZMD5_Hash[2] += c;
	rZMD5_Hash[3] += d;
}
void ZMD5_Feed(const unsigned char* iData, size_t iLength) {
    size_t lIndex = rZMD5_Counter[0] / 8 % 64;
    if ((rZMD5_Counter[0] += (iLength << 3)) < (iLength << 3)) {rZMD5_Counter[1]++;}
    rZMD5_Counter[1] += (iLength >> 29);
    size_t firstpart = 64 - lIndex;
    size_t i;
    if (iLength >= firstpart) {
        for (size_t lCopy = 0; lCopy < firstpart; lCopy++) {rZMD5_Buffer[lIndex + lCopy] = iData[lCopy];}
        ZMD5_Transform(rZMD5_Buffer);
        for (i = firstpart; i + 64 <= iLength; i += 64) {ZMD5_Transform(&iData[i]);}
        lIndex = 0;
    } else {
		i = 0;
	}
    for (size_t lCopy = 0; lCopy < (iLength - i); lCopy++) {rZMD5_Buffer[lIndex + lCopy] = iData[i + lCopy];}
}
void ZMD5_Init(void) {
    rZMD5_Counter[0] = 0x0;
    rZMD5_Counter[1] = 0x0;
    rZMD5_Hash[0] = 0x67452301;
    rZMD5_Hash[1] = 0xefcdab89;
    rZMD5_Hash[2] = 0x98badcfe;
    rZMD5_Hash[3] = 0x10325476;
}
void ZMD5_Finish(void) {
    rZMD5_Size[0] = rZMD5_Counter[0];
    rZMD5_Size[1] = rZMD5_Counter[1];
    size_t lIndex = rZMD5_Counter[0] / 8 % 64;
    size_t lPaddingLength = (lIndex < 56) ? (56 - lIndex) : (120 - lIndex);
    ZMD5_Feed(rZMD5_Padding, lPaddingLength);
    ZMD5_Feed((const unsigned char*)rZMD5_Size, 8);
}
unsigned long long ZMD5_Size(void) {
    return (((unsigned long long)rZMD5_Size[1] << 29) | (rZMD5_Size[0] >> 3));
}
const char* ZMD5_Digest(void) {
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int ii = 0; ii < 4; ii++) {
            unsigned char lByte = (rZMD5_Hash[i] >> (8 * ii)) & 0xff;
            unsigned int lDigit = (lByte >> 4);
            rZMD5_Digest[2 * (4 * i + ii)] = lDigit + ((lDigit > 9) ? 0x57 : 0x30);
            lDigit = (lByte & 0xf);
            rZMD5_Digest[2 * (4 * i + ii) + 1] = lDigit + ((lDigit > 9) ? 0x57 : 0x30);
        }
    }
    rZMD5_Digest[32] = '\0';
    return rZMD5_Digest;
}
const char* ZMD5_HashData(const unsigned char* iData, size_t iLength) {
    if (iData != NULL) {
        ZMD5_Init();
		ZMD5_Feed(iData, iLength);
		ZMD5_Finish();
		return ZMD5_Digest();
    } else {
        rZMD5_Digest[0] = '\0';
        return rZMD5_Digest;
    }
}
const char* ZMD5_HashText(const char* iText) {
    if (iText != NULL) {
        size_t lLength = -1;
        while (iText[++lLength]);
        ZMD5_Init();
		ZMD5_Feed((const unsigned char*)iText, lLength);
		ZMD5_Finish();
		return ZMD5_Digest();
    } else {
        rZMD5_Digest[0] = '\0';
        return rZMD5_Digest;
    }
}

#endif // ZMD5_C_INCLUDED
