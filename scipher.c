#include <string.h>

#define asciiMaxValue 127

char * convertToCipher(char *text) {
    static char output[255] = "CC&";
    for (int i = 0; i < strlen(text); i++) {
        int charInt = (int) text[i];
        if (charInt < (asciiMaxValue / 2)) {
            char newC = (int) ((double)charInt * 1.5)+'0';
            strncat(output, &newC, 1);
        } else {
            char newC = (int) ((double)charInt / 2)+'0';
            strncat(output, &newC, 1);
        }
    }
    return output;
}