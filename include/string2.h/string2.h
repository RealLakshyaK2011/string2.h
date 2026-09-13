#include <stddef.h>
#include <stdio.h>
#ifndef _STRING2_H_H_
#define _STRING2_H_H_ 1

#define BUFFER_SIZE 128
#define BBUFFER_STEP 8

#define STRING_BUFFER_STEP 128

typedef unsigned int uint;

// bbI points to the in use buffer.
// bI points to the next character's address in the buffer.
typedef struct
{
    uint bbuffer_size, buffers_initialized;
    uint bbI, bI;
    char **bbuffer;
} string2_builder;

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

char* string2_builder_build_cstring(string2_builder* builder, uint* length);
void  string2_builder_build_cstring_to(string2_builder* builder, char* cstring);
void  string2_builder_build_string2(string2_builder* builder, string2* str);

size_t string2_builder_get_length(string2_builder* builder);
char   string2_builder_getchar(string2_builder* builder, size_t index);
void   string2_builder_putchar(string2_builder* builder, size_t index, char c);

// string2 functions
void make_string2(string2* string, char* cstring);
void make_string2_size(string2* string, size_t initsize);
void dealloc_string2(string2* string);

void string2_concat_char(string2* string, char c);
void string2_concat_cstring_auto(string2* string, char* cstring);
void string2_concat_cstring(string2* string, char* cstring, size_t length);
void string2_concat_string2(string2* string, string2* str2);

void string2_readword(string2* string, FILE* stream);
void string2_readline(string2* string, FILE* stream);

#endif
