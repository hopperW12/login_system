#include <string.h>
#include <stdlib.h>

#define asciiMaxValue 127

char *convertToCipher(char *text) {
    char *output = calloc(strlen(text)+3, sizeof(char));

    strcat(output, "SS&");

    for (int i = 0; i < strlen(text); i++) {

        int charInt = (int) text[i];
        if (charInt < 33) {
            char newC = (char) charInt;
            strncat(output, &newC, 1);

        } else if (charInt < (asciiMaxValue / 2)) {
            char newC = (char) ((double) charInt * 1.5);
            strncat(output, &newC, 1);

        } else {

            char newC = (char) ((double) charInt / 2);
            strncat(output, &newC, 1);
        }
    }
    return output;
}