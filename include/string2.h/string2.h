#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#ifndef _STRING2_H_H_
#define _STRING2_H_H_ 1

#define BUFFER_SIZE 128
#define BBUFFER_STEP 8

#define STRING_BUFFER_STEP 128

typedef unsigned int uint;

// bbuffer: short of buffer of buffer, a buffer containing pointers to total allocated buffers
// bbuffer_size: the size of bbuffer
// buffers_initialized: total number of buffers that have been allocated/initialized
// bbI: index pointing to the latest buffer in bbuffer
// bI: index pointing to the next character to be written in the latest buffer
typedef struct
{
    size_t bbuffer_size, buffers_initialized;
    size_t bbI, bI;
    char **bbuffer;
} string2_builder;

// length: length of the string, excluding null term
// allocated: total number of allocated bytes
// string: null terminated string, the data
typedef struct
{
    size_t length, allocated;
    char* string;
} string2;

// string2_builder functions
void make_string2_builder(string2_builder* builder);
void dealloc_string2_builder(string2_builder* builder);

void string2_builder_append_char(string2_builder* builder, char c);
void string2_builder_append_cstring_auto(string2_builder* builder, char* cstring);
void string2_builder_append_cstring(string2_builder* builder, char* cstring, size_t length);
void string2_builder_append_string2(string2_builder* builder, string2* str);

char* string2_builder_build_cstring(string2_builder* builder, size_t* length);
void  string2_builder_build_cstring_to(string2_builder* builder, char* cstring);
void  string2_builder_build_string2(string2_builder* builder, string2* str);

void string2_builder_readword(string2_builder* builder, FILE* stream);
void string2_builder_readline(string2_builder* builder, FILE* stream);

size_t string2_builder_get_length(string2_builder* builder);
char   string2_builder_getchar(string2_builder* builder, size_t index);
void   string2_builder_putchar(string2_builder* builder, size_t index, char c);

// string2 functions
void make_string2(string2* string, const char* cstring);
void make_string2_size(string2* string, size_t initsize);
void dealloc_string2(string2* string);

void string2_concat_char(string2* string, char c);
void string2_concat_cstring(string2* string, char* cstring);
void string2_concat_pstring(string2* string, char* cstring, size_t length);
void string2_concat_string2(string2* string, string2* str2);

void string2_readword(string2* string, FILE* stream);
void string2_readline(string2* string, FILE* stream);

char string2_getchar(string2* string, size_t index, bool* outofbounds);
void string2_putchar(string2* string, size_t index, char c);

#endif
