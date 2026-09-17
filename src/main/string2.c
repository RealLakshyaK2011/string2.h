#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string2.h/string2.h"

// Declarations
void allocate_blocks(string2* string, size_t size, bool re);

// Constructors/Destructors
void make_string2(string2 *string, const char *cstring)
{
    size_t len = strlen(cstring);
    string->allocated = 0;
    allocate_blocks(string, len+1, false); // Allocate +1 for null term.
    
    strncpy(string->string, cstring, len);
    string->length = len;
}

void make_string2_size(string2* string, size_t initsize)
{
    allocate_blocks(string, initsize, false);
    string->string[0] = '\0';
    string->length = 0;
}

void dealloc_string2(string2* string)
{
    free(string->string);
}

// Concatenators
void string2_concat_char(string2* string, char c)
{
    size_t len = string->length; 
    if(len + 2 > string->allocated) // len+1 is new length, +1 for the null term.
    {
        allocate_blocks(string, 1, true);
    }

    // Concat the character, concat null term after that
    string->string[len] = c;
    string->string[len+1] = '\0';
    string->length++;
}

void string2_concat_cstring(string2* string, const char* const cstring)
{
    string2_concat_pstring(string, cstring, strlen(cstring));
}

void string2_concat_pstring(string2* string, const char* const pstring, size_t length)
{
    size_t strlen = string->length;
    if(strlen + length + 1 > string->allocated) allocate_blocks(string, length, true); // +1 for null term

    strncpy(string->string+strlen, pstring, length);
    string->string[strlen+length] = '\0';
    string->length += length;
}

void string2_concat_string2(string2 *string, string2 *str2)
{
    size_t strlen = string->length;
    if(strlen + str2->length + 1 > string->allocated) allocate_blocks(string, str2->length, true); // +1 for null term

    strncpy(string->string+strlen, str2->string, str2->length);
    string->length += str2->length;
    string->string[string->length] = '\0';
}

// Reader
void readcommon(string2 *string, FILE *stream, bool word)
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
        if(c == EOF || (word && (c == ' ' || c == '\t'))) break;
        if(c == '\r')
        {
            bufferCR = true;
            continue;
        }
        string2_concat_char(string, c);
    }
}

void string2_readword(string2* string, FILE* stream)
{
    readcommon(string, stream, true);
}

void string2_readline(string2 *string, FILE *stream)
{
    readcommon(string, stream, false);
}

char string2_getchar(string2* string, size_t index, bool* outofbounds)
{
    if(index >= string->length)
    {
        if(outofbounds != NULL) *outofbounds = true;
        return 0;
    }
    return string->string[index];
}

void string2_putchar(string2* string, size_t index, char c)
{
    if(index >= string->length-1) return;
    string->string[index] = c;
}

// Private
void allocate_blocks(string2* string, size_t size, bool re)
{
    if(size == 0) return;
    string->allocated += size;
    string->allocated += STRING_BUFFER_STEP - (string->allocated % STRING_BUFFER_STEP);

    string->string = re ? realloc(string->string, string->allocated) : malloc(string->allocated);
}