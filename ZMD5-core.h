/*** Copyright (C) 2020-2025 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef ZMD5_CORE_H_INCLUDED
#define ZMD5_CORE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void ZMD5_Init(void);
void ZMD5_Feed(const unsigned char* iData, size_t iLength);
void ZMD5_Finish(void);
unsigned long long ZMD5_Size(void);
const char* ZMD5_Digest(void);
#ifdef ZMD5__TEST__
const char* ZMD5_HashText(const char* iText);
#endif // ZMD5__TEST__
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ZMD5_CORE_H_INCLUDED
