#include "stdio.h"
#include "stdlib.h"

typedef struct {
    uint64_t *items;
    uint64_t size;
    uint64_t limit;
} IntArray;

void new_array(IntArray *array) {
    array->size = 0;
    array->limit = 128;
    array->items = malloc(array->limit * sizeof(int*));
}

void add_to_array(IntArray *array, int value) {
    if (array->size == array->limit) {
        array->limit *= 2;
        array->items = realloc(array->items, array->limit * sizeof(uint64_t*));
    }

    array->items[array->size++] = value;
}

void free_array(IntArray *array) {
    free(array->items);
    free(array);
}

void print_timers(IntArray *timers) {
    for (int i = 0; i < timers->size; i++) {
        printf("%llu ", timers->items[i]);
    }

    puts("\n");
}

int run_timers(IntArray *timers, int days, uint64_t toAdd) {
    if (days == 0) {
        return timers->size;
    }

    for (int i = 0; i < toAdd; i++) {
        add_to_array(timers, 9);
    }

    toAdd = 0;
    uint64_t count = timers->size;
    for (uint64_t i = 0; i < count; i++) {
        uint64_t *value = &timers->items[i];
        *value = *value - 1;

        if (*value == 0) {
            *value = 7;
            toAdd++;
        }
    }

    return run_timers(timers, --days, toAdd);
}

int main() {
    FILE *file = fopen("simple.txt", "r");
    if (file == NULL) {
        return 1;
    }

    IntArray *timers = malloc(sizeof(IntArray*));
    new_array(timers);

    char c;
    while((c = fgetc(file)) != EOF) {
        if (c == ',') continue;

        add_to_array(timers, c - '0');
    }
    fclose(file);

    int days = 256;
    uint64_t count = run_timers(timers, days, 0);
    printf("%llu fishes after %d days! \n", count, days);

    free_array(timers);
    return 0;
}