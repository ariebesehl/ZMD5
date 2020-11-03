/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef ZMD5_H_INCLUDED
#define ZMD5_H_INCLUDED

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZMD5_Init(void);
void ZMD5_Feed(const unsigned char* iData, size_t iLength);
void ZMD5_Finish(void);
unsigned long long ZMD5_Size(void);
const char* ZMD5_Digest(void);
const char* ZMD5_HashData(const unsigned char* iData, size_t iLength);
const char* ZMD5_HashText(const char* iText);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZMD5_H_INCLUDED
