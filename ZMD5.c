/*** Copyright (C) 2020-2025 Andreas 'cr4qsh0t' Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#include <stdlib.h>
#include <stdio.h>
#include "ZMD5-core.h"

#if defined(__WIN32) || defined(_WIN32) || defined(WIN32) || defined(__WIN64) || defined(_WIN64) || defined(WIN64)
    #include <io.h>
    #include <fcntl.h>
    #define ZMD5_BINARY_STDIN() setmode(STDIN_FILENO, O_BINARY)
    #define ZMD5_WINDOWS
#else
    #define ZMD5_BINARY_STDIN()
#endif // OS MULTIPLEXER

//#define ZMD5_USE_HEAP
#define ZMD5_BUFFER_SIZE 1048576 * 2
#ifdef ZMD5_USE_HEAP
    static unsigned char* gBuffer;
#else
    static unsigned char gBuffer[ZMD5_BUFFER_SIZE];
#endif // ZMD5_USE_HEAP

#define ZMD5_MSG_NAME "ZMD5"
#define ZMD5_MSG_VERSION "20240211"
#define ZMD5_MSG_AUTHOR "cr4qsh0t"
#define ZMD5_MSG_HELP "Usage: " ZMD5_MSG_NAME " <filename(s)|stdin>"
#define ZMD5_MSG_NOMEM "error: cannot allocate buffer"
#define ZMD5_MSG_NOFILE "error: cannot open as file %s"
#ifdef ZMD5_WINDOWS
    #define ZMD5_MSG_LIST "%s\t%I64u\t%s"
#else
    #define ZMD5_MSG_LIST "%s\t%llu\t%s"
#endif // ZMD5_WINDOWS

#define ZMD5_MSG_MOTD ZMD5_MSG_NAME " -- v" ZMD5_MSG_VERSION " -- " ZMD5_MSG_AUTHOR " -- " ZMD5_MSG_HELP

static void gZMD5_Hash(FILE* iFile) {
    static size_t lBytesRead;
    ZMD5_Init();
    do {ZMD5_Feed(gBuffer, (lBytesRead = fread(gBuffer, 1, ZMD5_BUFFER_SIZE, iFile)));} while (lBytesRead == ZMD5_BUFFER_SIZE);
    ZMD5_Finish();
}
int main(int iArgC, char** iArgV) {
    int lError = 0;
    fprintf(stderr, ZMD5_MSG_MOTD "\n");
#ifdef ZMD5_USE_HEAP
    if ((gBuffer = (unsigned char*)malloc(ZMD5_BUFFER_SIZE)) != NULL) {
#endif // ZMD5_USE_HEAP
		if (iArgC > 1) {
			for (int i = 1; i < iArgC; ++i) {
				if (iArgV[i] != NULL) {
					FILE* lFile;
					if ((lFile =  fopen(iArgV[i], "rb")) != NULL) {
						gZMD5_Hash(lFile);
						printf(ZMD5_MSG_LIST "\n", ZMD5_Digest(), ZMD5_Size(), iArgV[i]);
						fclose(lFile);
					} else {
						++lError;
						fprintf(stderr, ZMD5_MSG_NOFILE "\n", iArgV[i]);
					}
				}
			}
		} else {
			ZMD5_BINARY_STDIN();
			gZMD5_Hash(stdin);
			printf(ZMD5_MSG_LIST "\n", ZMD5_Digest(), ZMD5_Size(), "<stdin>");
		}
#ifdef ZMD5_USE_HEAP
		free(gBuffer);
	} else {
		fprintf(stderr, ZMD5_MSG_NOMEM "\n");
	}
#endif // ZMD5_USE_HEAP
    return lError;
}
