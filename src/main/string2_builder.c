#include "string2.h/string2.h"
#include <stdlib.h>

// Functions Declarations
void make_buffer(string2_builder* builder);
void make_buffers(string2_builder* builder, uint n);

// Public functions
void make_string2_builder(string2_builder* builder)
{
    builder->bbuffer_size =  BBUFFER_STEP;
    builder->buffers_initialized = 1;
    builder->bbI = 0; builder->bI = 0;
    builder->bbuffer = malloc(sizeof(char*) * BBUFFER_STEP);
    builder->bbuffer[0] = malloc(sizeof(char) * BUFFER_SIZE);
}

void dealloc_string2_builder(string2_builder *builder)
{
    for(int i = 0; i < builder->buffers_initialized; i++)
    {
        free(builder->bbuffer[i]);
    }
    free(builder->bbuffer);
}

// Appending function
void string2_builder_append_char(string2_builder *builder, char c)
{
    if(builder->bI >= BUFFER_SIZE)
    {
        if(builder->bbI+1 >= builder->buffers_initialized) make_buffer(builder);
        builder->bbI++; builder->bI = 0;
    }
    
    builder->bbuffer[builder->bbI][builder->bI] = c;
    builder->bI++;
}

void string2_builder_append_cstring_auto(string2_builder* builder, char* cstring)
{
    size_t length = 0; char c;
    while((c = cstring[length]) != '\0') length++;

    string2_builder_append_cstring(builder, cstring, length);
}

// Length excludes null terminator '\0'
void string2_builder_append_cstring(string2_builder *builder, char *cstring, size_t length)
{
    size_t t = length;
    t -= BUFFER_SIZE - builder->bI; // Space left in current buffer
    t = t / BUFFER_SIZE + (t % BUFFER_SIZE == 0 ? 0 : 1); // Equivalent of doing roof on a float number
    make_buffers(builder, t);

    for(int i = 0; i < length; i++)
    {
        if(builder->bI >= BUFFER_SIZE)
        {
            builder->bbI++;
            builder->bI = 0;
        }
        builder->bbuffer[builder->bbI][builder->bI] = cstring[i];
        builder->bI++;
    }
}

void string2_builder_append_string2(string2_builder* builder, string2* str)
{
    // Calculate required amount of buffers
    size_t t = str->length - 1; // -1 excludes null terminator
    t -= BUFFER_SIZE - builder->bI; // Space left in current buffer
    t = t / BUFFER_SIZE + (t % BUFFER_SIZE == 0 ? 0 : 1); // Equivalent of doing roof on a float number
    make_buffers(builder, t);

    for(int i = 0; i < str->length; i++)
    {
        if(builder->bI >= BUFFER_SIZE)
        {
            builder->bbI++;
            builder->bI = 0;
        }
        builder->bbuffer[builder->bbI][builder->bI] = str->string[i];
        builder->bI++;
    }
}

// Building function
char* string2_builder_build_cstring(string2_builder* builder, size_t* length)
{
    size_t l = string2_builder_get_length(builder);
    char* cstr = malloc(sizeof(char) * (l + 1));
    string2_builder_build_cstring_to(builder, cstr);
    if(length != NULL) *length = l+1;
    return cstr;
}

void string2_builder_build_cstring_to(string2_builder *builder, char* cstring)
{
    size_t length = string2_builder_get_length(builder);

    for(int i = 0; i <= builder->bbI; i++)
    {
        for(int j = 0; j < (i == builder->bbI ? builder->bI : BUFFER_SIZE); j++)
        {
            char* buffer = builder->bbuffer[i];
            char c = buffer[j];
            cstring[i * BUFFER_SIZE + j] = c;
        }
    }
    cstring[length] = '\0';
}

void string2_builder_build_string2(string2_builder *builder, string2 *str)
{
    // +1 for null terminator '\0'
    size_t len = string2_builder_get_length(builder) + 1;
    make_string2_size(str, len);

    for(int i = 0; i <= builder->bbI; i++)
    {
        for(int j = 0; j < (i == builder->bbI ? builder->bI : BUFFER_SIZE); j++)
        {
            char* buffer = builder->bbuffer[i];
            char c = buffer[j];
            str->string[i * BUFFER_SIZE + j] = c;
        }
    }

    str->string[len-1] = '\0';
}

// Getter/Setter
size_t string2_builder_get_length(string2_builder* builder)
{
    return builder->bbI * BUFFER_SIZE + builder->bI;
}

char string2_builder_getchar(string2_builder* builder, size_t index)
{
    if(index >= string2_builder_get_length(builder)) return 0;
    return builder->bbuffer[index/BUFFER_SIZE][index%BUFFER_SIZE];
}

void string2_builder_putchar(string2_builder* builder, size_t index, char c)
{
    if(index >= string2_builder_get_length(builder)) return;
    builder->bbuffer[index/BUFFER_SIZE][index%BUFFER_SIZE] = c;
}


// Private functions: buffer initialization
void make_buffer(string2_builder* builder)
{
    if(builder->buffers_initialized + 1 > builder->bbuffer_size)
    {
        builder->bbuffer_size += BBUFFER_STEP;
        builder->bbuffer = realloc(builder->bbuffer, sizeof(char*) * builder->bbuffer_size);
    }

    size_t buffer_index = builder->buffers_initialized;
    builder->bbuffer[buffer_index] = malloc(sizeof(char) * BUFFER_SIZE);
    builder->buffers_initialized++;
}

void make_buffers(string2_builder* builder, uint n)
{
    if(n == 0) return;

    if(builder->buffers_initialized + n > builder->bbuffer_size)
    {
        builder->bbuffer_size += n;
        builder->bbuffer_size += BBUFFER_STEP - (builder->bbuffer_size % BBUFFER_STEP);
        builder->bbuffer = realloc(builder->bbuffer, sizeof(char*) * builder->bbuffer_size);
    }

    for(int i = 0; i < n; i++)
    {
        size_t buffer_index = builder->buffers_initialized;
        builder->bbuffer[buffer_index] = malloc(sizeof(char) * BUFFER_SIZE);
        builder->buffers_initialized++;
    }
}
