#include "stdio.h"

void part1(FILE *file) {
    int increments = 0;
    char line[16] = "";

    int *prev = NULL;
    while(fgets(line, sizeof(line), file)) {
        if (prev != NULL) {
            int curr;
            sscanf(line, "%d", &curr);

            if (curr > *prev) {
                increments++;
            }

            *prev = curr;
        } else {
            int value;
            sscanf(line, "%d", &value);

            prev = &value;
        }
    }

    printf("Depth increased %d times!\n", increments);
}

void part2(FILE *file) {
    int increments = 0;
    char line[16] = "";

    int groupSize = 3;

    int *prev = NULL;
    int prevGroup[groupSize];
    int i = 0;
    while(fgets(line, sizeof(line), file)) {
        i = i % groupSize;

        int curr;
        sscanf(line, "%d", &curr);

        prevGroup[i] = curr;
        if (i == groupSize - 1 && prev == NULL) {
            int value = prevGroup[0] + prevGroup[1] + prevGroup[2];
            prev = &value;
        } else if (prev != NULL) {
            int value = prevGroup[0] + prevGroup[1] + prevGroup[2];
            if (value > *prev) {
                increments++;
            }

            *prev = value;
        }

        i++;
    }

    printf("Depth increased %d times!\n", increments);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    part1(file);
    fseek(file, 0, SEEK_SET);

    part2(file);

    fclose(file);
    return 0;
}
