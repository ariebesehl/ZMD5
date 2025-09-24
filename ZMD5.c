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

#define ZMD5_BUFFER_SIZE (1048576 * 2)
static unsigned char gBuffer[ZMD5_BUFFER_SIZE];

#define ZMD5_MSG_NAME		"zmd5"
#define ZMD5_MSG_VERSION	"v250906"
#define ZMD5_MSG_AUTHOR		"cr4qsh0t"
#define ZMD5_MSG_HELP		"usage: " ZMD5_MSG_NAME " <files|stdin>"
#define ZMD5_MSG_NOFILE		"wrn: cannot open as file %s"
#define ZMD5_MSG_READ		"wrn: could not open %d path(s)"
//#define ZMD5_MSG_MOTD		ZMD5_MSG_NAME " -- " ZMD5_MSG_VERSION " -- " ZMD5_MSG_AUTHOR " -- " ZMD5_MSG_HELP
#ifdef ZMD5_WINDOWS
	#define ZMD5_MSG_LIST	"%s\t%I64u\t%s"
#else
	#define ZMD5_MSG_LIST	"%s\t%llu\t%s"
#endif // ZMD5_WINDOWS

// ...I'm running this through a buffer instead of reading (and crunching) straight from the file descriptor, right?
void gZMD5_Hash(FILE* iFile) {
	static size_t lBytesRead;
	ZMD5_Init();
	do {ZMD5_Feed(gBuffer, (lBytesRead = fread(gBuffer, 1, ZMD5_BUFFER_SIZE, iFile)));} while (lBytesRead == ZMD5_BUFFER_SIZE);
	ZMD5_Finish();
}
int main(int iArgC, char** iArgV) {
	int lError = 0;
	#ifdef ZMD5_MSG_MOTD
	fprintf(stderr, ZMD5_MSG_MOTD "\n");
	#endif // ZMD5_MSG_MOTD
	if (iArgC > 1) {
		for (int i = 1; i < iArgC; ++i) {
			if (iArgV[i] != NULL) {
				FILE* lFile;
				if ((lFile =  fopen(iArgV[i], "rb")) != NULL) {
					gZMD5_Hash(lFile);
					fclose(lFile);
					printf(ZMD5_MSG_LIST "\n", ZMD5_Digest(), ZMD5_Size(), iArgV[i]);
				} else {
					++lError;
					fprintf(stderr, ZMD5_MSG_NOFILE "\n", iArgV[i]);
				}
			}
		}
		if (lError) {fprintf(stderr, ZMD5_MSG_READ "\n", lError);}
	} else {
		ZMD5_BINARY_STDIN();
		gZMD5_Hash(stdin);
		printf(ZMD5_MSG_LIST "\n", ZMD5_Digest(), ZMD5_Size(), "<stdin>");
	}
	return 0;
}
