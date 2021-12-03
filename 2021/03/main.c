#include "stdio.h"
#include "stdlib.h"

#define DIGIT_COUNT 12

int calculate_gamma_rate(int digits[]) {
    int result = 0;
    for (int i = 0; i < DIGIT_COUNT; i++) {
        int bit;
        if (digits[i] > 0) {
            bit = 1;
        } else if (digits[i] < 0) {
            continue;
        } else {
            exit(EXIT_FAILURE);
        }

        int mask = 1 << (DIGIT_COUNT - i - 1);
        result |= mask;
    }

    return result;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int binaryDigits[DIGIT_COUNT] = { 0 };
    char line[DIGIT_COUNT + 2] = "";
    while(fgets(line, sizeof(line), file)) {
        for (int i = 0; i < DIGIT_COUNT; i++) {
            int bit = line[i] - '0';
            if (bit == 0) {
                bit = -1;
            }

            binaryDigits[i] += bit;
        }
    }

    int gammaRate = calculate_gamma_rate(binaryDigits);
    int epsilonRate = 0xfff ^ gammaRate;

    printf("Power amount to %d!\n", gammaRate * epsilonRate);
    
    fclose(file);
    return 0;
}