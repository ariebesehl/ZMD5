/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#include <stdio.h>
#include <stdlib.h>
#include "ZMD5.h"

#if defined(_WIN32) || defined(_WIN32) || defined(WIN32) || defined(__WIN64) || defined(_WIN64) || defined(WIN64)
#include <io.h>
#include <fcntl.h>
#define ZMD5_BINARY_STDIN() setmode(STDIN_FILENO, O_BINARY)
#else
#define ZMD5_BINARY_STDIN()
#endif

#define ZMD5_MSG_NAME "ZMD5"
#define ZMD5_MSG_VERSION "20201105"
#define ZMD5_MSG_AUTHOR "cr4qsh0t"
#define ZMD5_MSG_DECOR "*---- "
#define ZMD5_MSG_DECOM " ------ "
#define ZMD5_MSG_DECOL " ----*"
#define ZMD5_MSG_HELP "Usage: " ZMD5_MSG_NAME " <filename>"
#define ZMD5_MSG_MOTD ZMD5_MSG_DECOR ZMD5_MSG_NAME " v" ZMD5_MSG_VERSION " by " ZMD5_MSG_AUTHOR ZMD5_MSG_DECOM ZMD5_MSG_HELP ZMD5_MSG_DECOL
#define ZMD5_MSG_DONE ZMD5_MSG_DECOR "done %d/%d" ZMD5_MSG_DECOL
#define ZMD5_MSG_NOMEM ZMD5_MSG_DECOM "error: cannot allocate buffer"
#define ZMD5_MSG_NOFILE ZMD5_MSG_DECOM "error: cannot open file"

#define ZMD5_BUFFER_SIZE 16777216
unsigned char* gBuffer;

void gZMD5_Hash(FILE* iFile) {
    size_t lBytesRead;
    ZMD5_Init();
    do {ZMD5_Feed(gBuffer, (lBytesRead = fread(gBuffer, 1, ZMD5_BUFFER_SIZE, iFile)));} while (lBytesRead == ZMD5_BUFFER_SIZE);
    ZMD5_Finish();
}
int main(int iCount, char** iValues) {
    fprintf(stderr, ZMD5_MSG_MOTD "\n");
    if ((gBuffer = (unsigned char*)malloc(ZMD5_BUFFER_SIZE)) != NULL) {
        if (iCount > 1) {
            int lError = 0;
            for (int i = 1; i < iCount; i++) {
                if (iValues[i] != NULL) {
                    FILE* lFile;
                    if ((lFile =  fopen(iValues[i], "rb")) != NULL) {
                        gZMD5_Hash(lFile);
                        printf("%s\t%s (%I64u bytes)\n", ZMD5_Digest(), iValues[i], ZMD5_Size());
                        fclose(lFile);
                    } else {
                        lError++;
                        fprintf(stderr, ZMD5_MSG_NOFILE " \"%s\"\n", iValues[i]);
                    }
                }
            }
            fprintf(stderr, ZMD5_MSG_DONE, iCount - 1 - lError, iCount - 1);
        } else {
            ZMD5_BINARY_STDIN();
            gZMD5_Hash(stdin);
            printf("%s\t%s (%I64u bytes)\n", ZMD5_Digest(), "<stdin>", ZMD5_Size());
            fprintf(stderr, ZMD5_MSG_DONE, 1, 1);
        }
        free(gBuffer);
    } else {
        fprintf(stderr, ZMD5_MSG_NOMEM "\n");
    }
    return 0;
}
