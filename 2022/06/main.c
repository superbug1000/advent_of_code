#include "stdio.h"
#include "stdbool.h"

#define MARKER 14

bool unique_array(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == i) break;
            if (arr[i] == arr[j]) return false;
        }
    }

    return true;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    char tester[MARKER];
    char line[5000];
    fgets(line, sizeof(line), file);
    for (int i = 0; line[i] > 0; i++) {
        tester[i % MARKER] = line[i];

        if (i >= MARKER - 1 && unique_array(tester, MARKER)) {
            printf("First marker after character %d\n", i + 1);
            break;
        }
    }

    fclose(file);
    return 0;
}
