#include <stdio.h>
#include "string2.h/string2.h"

int main()
{
    string2 a, b;
    make_string2(&a, "\0");
    make_string2(&b, "\0");

    string2_readline(&a, stdin);
    string2_readline(&b, stdin);

    printf("The two read strings are:\n%s\n%s\n", a.string, b.string);

    dealloc_string2(&a); 
    dealloc_string2(&b);
    make_string2(&a, "\0");
    make_string2(&b, "\0");

    string2_readword(&a, stdin);
    string2_readword(&b, stdin);

    printf("The two whitespace separated words are: [%s] and [%s]\n", a.string, b.string);

    return 0;
}