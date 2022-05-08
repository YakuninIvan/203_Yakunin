#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* func(const char* s, const char* pattern,
                  const char* replacement)
{
    char* result;
    int i, patterncounter = 0;
    int replacementlen = strlen(replacement);
    int patternlen = strlen(pattern);

    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], pattern) == &s[i]) {
            patterncounter++;
            i += patternlen - 1;
        }
    }

    result = (char*)malloc(i + patterncounter * (replacementlen - patternlen) + 1);

    i = 0;
    while (*s) {
        if (strstr(s, pattern) == s) {
            strcpy(&result[i], replacement);
            i += replacementlen;
            s += patternlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    char *pattern = argv[1];
    char *text = argv[2];
    char *replacement = argv[3];
    char* res = NULL;

    printf("old text: %s\n", text);
    res = func(text, pattern, replacement);
    printf("new text: %s\n", res);

    free(res);

    return 0;
}
