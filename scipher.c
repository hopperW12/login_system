#include <string.h>
#include <stdio.h>

#define asciiMaxValue 256

char *convertToCipher(char *text) {
    char output[255] = "CC&";
    for (int i = 0; i < strlen(text); i++) {
        int charInt = (int) text[i];
        char c = text[i];
        strcpy(output, &c);
        /*if (charInt < (asciiMaxValue / 2)) {
            char newC = (int) ((double)charInt * 1.5)+'0';
            strncat(output, &newC, 1);
        } else {
            char newC = (int) ((double)charInt / 2)+'0';
            strncat(output, &newC, 1);
        }*/
    }
    printf("%s\n", output);
    return output;
}