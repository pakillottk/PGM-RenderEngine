#include "IO.h"

#include <stdlib.h>
#include <stdio.h>

unsigned getFileSize(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    unsigned bytes = ftell(fp);
    rewind(fp);

    return bytes;
}

// CAUTION: buffer returned should be realeased
char* IO::readRawBytes(const char* file)
{
    FILE* fp = fopen(file, "r");
    if(fp == NULL)
    {
        return NULL;
    }

    unsigned size = getFileSize(fp);

     // Allocate a string that can hold it all
    char* buffer = (char*) malloc(sizeof(char) * (size + 1) );

    // Read it all in one operation
    fread(buffer, sizeof(char), size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[size] = '\0';

    fclose(fp);

    return buffer;
}

const char* IO::readTextFile(const char* file)
{
    char* bytes = readRawBytes(file);
    if(bytes == NULL)
    {
        return NULL;
    }

    return bytes;
}