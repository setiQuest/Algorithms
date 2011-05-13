#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "sq_dsp.h"

unsigned int smpls_len = 100000;

void mylog(char *msg);

int main(int argc, char **argv)
{

    int opt;

    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &smpls_len);
                break;
        }
    }
    
    int status = sq_sum(stdin, stdout, smpls_len);
    
    if(status < 0)
    {
        printf("sqsum [-l samples-block-size]\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}

