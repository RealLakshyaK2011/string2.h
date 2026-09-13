#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string2.h/string2.h"

// Declarations
void allocate_blocks(string2* string, size_t size, bool re);

// Constructors/Destructors
void make_string2(string2 *string, char *cstring)
{
    int len = 0;
    char c;
    while((c = cstring[len]) != '\0') len++;
    len++;

    allocate_blocks(string, len, false);
    
    for(int i = 0; i < len; i++)
    {
        string->string[i] = cstring[i];
    }

    string->length = len;
}

void make_string2_size(string2* string, size_t initsize)
{
    string->string = malloc(sizeof(char) * initsize);
}

void dealloc_string2(string2* string)
{
    free(string->string);
}

// Concatenators
void string2_concat_char(string2* string, char c)
{
    register size_t len = string->length; 
    if(len + 1 > string->allocated)
    {
        allocate_blocks(string, len + 1, false);
    }

    string->string[len-1] = c;
    string->string[len] = '\0';
    string->length++;
}

void string2_concat_cstring_auto(string2* string, char* cstring)
{
    size_t length = 0; char c;
    while((c = cstring[length]) != '\0') length++;

    string2_concat_cstring(string, cstring, length);
}

void string2_concat_cstring(string2 *string, char *cstring, size_t length)
{
    size_t strlen = string->length;
    if(strlen + length > string->allocated) allocate_blocks(string, length, false);
    for(int i = 0; i < length; i++)
    {
        string->string[strlen+i-1] = cstring[i];
    }
    string->string[strlen+length-1] = '\0';
    string->length += length;
}

void string2_concat_string2(string2 *string, string2 *str2)
{
    register size_t strlen = string->length;
    if(strlen+ str2->length > string->allocated)
    {
        allocate_blocks(string, str2->length, false);
    }

    for(int i = 0; i < str2->length; i++)
    {
        string->string[strlen+i-1] = str2->string[i];
    }
    string->length += str2->length-1;
}

// Reader
void string2_readword(string2 *string, FILE *stream)
{
    char c;
    bool bufferCR = 0;

    while(1)
    {
        c = fgetc(stream);
        if(c == ' ' || c == '\t' || c == '\n') break;
        if(bufferCR)
        {
            string2_concat_char(string, '\r');
            bufferCR = false;
        }
        if(c == '\r')
        {
            bufferCR = true;
            continue;
        }
        string2_concat_char(string, c);
    }
}

void string2_readline(string2 *string, FILE *stream)
{
    char c;
    bool bufferCR = 0;

    while(1)
    {
        c = fgetc(stream);
        if(c == '\n') break;
        if(bufferCR)
        {
            string2_concat_char(string, '\r');
            bufferCR = false;
        }
        if(c == '\r')
        {
            bufferCR = true;
            continue;
        }
        string2_concat_char(string, c);
    }
}

// Private
void allocate_blocks(string2* string, size_t size, bool re)
{
    if(size == 0) return;
    string->allocated += size;
    string->allocated += STRING_BUFFER_STEP - (string->allocated % STRING_BUFFER_STEP);

    string->string = re ? realloc(string->string, sizeof(char) * string->allocated) : malloc(sizeof(char) * string->allocated);
}