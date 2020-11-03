/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#include <stdio.h>
#include <stdlib.h>
#include "ZMD5.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define ZMD5_BINARY_STDIN() setmode(STDIN_FILENO, O_BINARY)
#else
#define ZMD5_BINARY_STDIN
#endif

#define ZMD5_MSG_NAME "ZMD5"
#define ZMD5_MSG_DECOR "*---- "
#define ZMD5_MSG_DECOM " ------ "
#define ZMD5_MSG_DECOL " ----*"
#define ZMD5_MSG_VERSION "20201102"
#define ZMD5_MSG_AUTHOR "cr4qsh0t"
#define ZMD5_MSG_HELP "Usage: " ZMD5_MSG_NAME " <filename>"
#define ZMD5_MSG_MOTD ZMD5_MSG_DECOR ZMD5_MSG_NAME " v" ZMD5_MSG_VERSION " by " ZMD5_MSG_AUTHOR ZMD5_MSG_DECOM ZMD5_MSG_HELP ZMD5_MSG_DECOL
#define ZMD5_MSG_ERR_NOMEM "error: cannot allocate buffer"
#define ZMD5_MSG_ERR_ISDIR "error: cannot open file"

#define ZMD5_BUFFER_SIZE 16777216
unsigned char* gBuffer;

void gZMD5_Hash(FILE* iFile) {
    size_t lBytesRead;
    ZMD5_Init();
    do {
        lBytesRead = fread(gBuffer, 1, ZMD5_BUFFER_SIZE, iFile);
        ZMD5_Feed((const unsigned char*)gBuffer, lBytesRead);
    } while (lBytesRead == ZMD5_BUFFER_SIZE);
    ZMD5_Finish();
}
int main(int argc, char *argv[]) {
    fprintf(stderr, ZMD5_MSG_MOTD);
    if ((gBuffer = (unsigned char*)malloc(ZMD5_BUFFER_SIZE)) != NULL) {
        if (argc > 1) {
            for (unsigned int i = 1; i < argc; i++) {
                if (argv[i] != NULL) {
                    FILE* lFile;
                    if ((lFile =  fopen(argv[i], "rb")) != NULL) {
                        gZMD5_Hash(lFile);
                        printf("\n%s\t%s (%I64u bytes)", ZMD5_Digest(), argv[i], ZMD5_Size());
                        fclose(lFile);
                    } else {
                        fprintf(stderr, "\n" ZMD5_MSG_ERR_ISDIR " \"%s\"", argv[i]);
                    }
                }
            }
        } else {
            ZMD5_BINARY_STDIN();
            gZMD5_Hash(stdin);
            printf("\n%s\t%s (%I64u bytes)", ZMD5_Digest(), "<stdin>", ZMD5_Size());
        }
        free(gBuffer);
    } else {
        fprintf(stderr, "\n" ZMD5_MSG_ERR_NOMEM);
    }
    return 0;
}
