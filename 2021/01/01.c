#include "stdio.h"

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

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
    return 0;
}
