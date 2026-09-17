#include <string2.h/string2.h>
#include <stdio.h>

int main()
{
    string2 str, rest;
    make_string2_size(&str, 23);
    make_string2(&rest, "wnies and chocolate ");

    string2_concat_char(&str, 'H');
    string2_concat_cstring(&str, "appy Henry ");
    string2_concat_pstring(&str, "likes beans, bro", 16);
    string2_concat_string2(&str, &rest);

    printf("What does henry like thats made of chocolate? and on what day does he like news?\n");
    string2_readword(&str, stdin);
    string2_concat_char(&str, ' ');
    string2_concat_cstring(&str, "over ");
    string2_readword(&str, stdin);
    string2_concat_cstring(&str, " news.\n");

    printf("So, %s", str.string);
}