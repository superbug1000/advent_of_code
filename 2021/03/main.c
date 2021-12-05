#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define DIGIT_COUNT 12

typedef struct {
    char **items;
    uint32_t size;
    uint32_t position;
} StringArray;

void new_array(StringArray *array) {
    array->position = 0;
    array->size = 128;
    array->items = malloc(array->size * sizeof(char*));

    for (int i = 0; i < array->size; i++) {
        array->items[i] = malloc(sizeof(char) * (DIGIT_COUNT));
    }
}

void add_to_array(StringArray *array, char *string) {
    if (array->position >= array->size) {
        array->size *= 2;
        array->items = realloc(array->items, array->size * sizeof(char*));

        for (int i = array->position; i < array->size; i++) {
            array->items[i] = malloc(sizeof(char) * (DIGIT_COUNT));
        }
    }

    strncpy(array->items[array->position++], string, DIGIT_COUNT);
}

void free_array(StringArray *array) {
    for (int i = 0; i < array->position; i++) {
        free(array->items[i]);
    }

    free(array->items);
    array->items = NULL;
}

StringArray* get_common_strings(StringArray *one_array, StringArray *zero_array, bool mostCommon) {
    StringArray *resultArray;
    if (mostCommon) {
        if (one_array->position >= zero_array->position) {
            resultArray = one_array;
            free_array(zero_array);
        } else {
            resultArray = zero_array;
            free_array(one_array);
        }
    } else {
        if (one_array->position < zero_array->position) {
            resultArray = one_array;
            free_array(zero_array);
        } else {
            resultArray = zero_array;
            free_array(one_array);
        }
    }

    return resultArray;
}

char* find_rating(StringArray *array, bool mostCommon, unsigned short bitPosition) {
    StringArray filtered_ones, filtered_zeros;
    new_array(&filtered_ones);
    new_array(&filtered_zeros);

    for (int i = 0; i < array->position; i++) {
        if (array->items[i][bitPosition] == '1') {
            add_to_array(&filtered_ones, array->items[i]);
        } else if (array->items[i][bitPosition] == '0') {
            add_to_array(&filtered_zeros, array->items[i]);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    StringArray *resultArray = get_common_strings(&filtered_ones, &filtered_zeros, mostCommon);
    if (resultArray->position == 1) {
        return resultArray->items[0];
    } else if (resultArray->position == 0) {
        free_array(resultArray);
        resultArray = NULL;
        return NULL;
    }

    char *rating = find_rating(resultArray, mostCommon, ++bitPosition);
    free_array(resultArray);
    resultArray = NULL;

    return rating;
}

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

    StringArray *binaryStrings = (StringArray*) (malloc(sizeof(StringArray)));
    new_array(binaryStrings);

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

        add_to_array(binaryStrings, line);
    }

    int gammaRate = calculate_gamma_rate(binaryDigits);
    int epsilonRate = 0xfff ^ gammaRate;

    printf("Power amounts to %d!\n", gammaRate * epsilonRate);

    char *oxygenRatingBinary = find_rating(binaryStrings, true, 0);
    long oxygenRating = strtol(oxygenRatingBinary, NULL, 2);
    printf("Oxygen rating -> %s - %ld\n", oxygenRatingBinary, oxygenRating);

    char *co2RatingBinary = find_rating(binaryStrings, false, 0);
    long co2Rating = strtol(co2RatingBinary, NULL, 2);
    printf("CO2 rating -> %s - %ld\n", co2RatingBinary, co2Rating);

    printf("Life support rating: %ld", oxygenRating * co2Rating);

    free_array(binaryStrings);
    fclose(file);
    return 0;
}