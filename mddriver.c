//
//  mddriver.c
//  MD5_RFC1321
//
//  Created by 张瑜 on 2017/12/9.
//  Copyright © 2017年 张瑜. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"

#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000


static void MDFile (char *);
static void MDPrint (uint8_t [16]);

/* Digests a file and prints the result.
 */
static void MDFile (char *filename) {
    FILE *file;
    MD5_CTX context;
    unsigned int last;
    unsigned long len;
    uint8_t buffer[4], digest[16];
    
    if ((file = fopen(filename, "r")) == NULL) {
        printf ("%s can't be opened\n", filename);
        exit(1);
    } else {
        MD5Init (&context);
        len = fread (buffer, 1, 4, file);
        
        fseek(file, 0L, SEEK_END);
        last = ftell(file);
        fclose(file);
        
        MD5Update (&context, buffer, last);
        
        MD5Final (digest, &context);
        
            
        printf ("MD5 (%s) = ", filename);
        MDPrint (digest);
        printf ("\n");
    }
}

/* Prints a message digest in hexadecimal.
 */
static void MDPrint (uint8_t digest[16]) {
    unsigned int i;
    for (i = 0; i < 16; i++) {
        printf ("%02x", digest[i]);
    }
}

int main (int argc, char * argv[]) {

    MDFile (argv[1]);
    
    return (0);
}
