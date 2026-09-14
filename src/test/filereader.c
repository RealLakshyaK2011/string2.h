#include <stdio.h>
#include "string2.h/string2.h"

int main(int argc, char* argv[])
{
    FILE* file;
    string2_builder content;
    make_string2_builder(&content);
    if(argc < 2) return 0;
    for(int i = 1; i < argc; i++)
    {
        char* path = argv[i];
        printf("Reading from file: %s\n", path);
        file = fopen(path, "r");
        if(file == NULL)
        {
            printf("Error reading file: %s!\n", path);
            continue;
        }

        string2_builder_append_cstring_auto(&content, "Read file: ");
        string2_builder_append_cstring_auto(&content, path);
        string2_builder_append_char(&content, '\n');
        while(!feof(file))
        {
            string2_builder_readline(&content, file);
            fflush(stdout);
            string2_builder_append_char(&content, '\n');
            fflush(stdout);
        }

        fclose(file);
    }

    
    char* readData = string2_builder_build_cstring(&content, NULL);
    printf("\n%s", readData);
    return 0;
}