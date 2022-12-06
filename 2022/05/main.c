#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define CRATE_COUNT 9
#define CRATE_LIMIT 512
#define PRESERVE_ORDER true

typedef struct {
    char array[CRATE_LIMIT];
    int top;
} Stack;

Stack *new_stack() {
    Stack *stack = calloc(1, sizeof(Stack));
    stack->top = -1;

    return stack;
}

void push_to_stack(Stack *stack, char value) {
    stack->array[++stack->top] = value;
}

char pop_stack(Stack *stack) {
    if (stack->top == -1) return 0;

    char c = stack->array[stack->top];
    stack->array[stack->top--] = 0;

    return c;
}

void shift(Stack *from, Stack *to, int count, bool preserve_order) {
    if (preserve_order) {
        char values[count];
        for (int i = 0; i < count; i++) {
            values[i] = pop_stack(from);
        }

        for (int i = count - 1; i >= 0; i--) {
            push_to_stack(to, values[i]);
        }
    } else {
        for (int i = 0; i < count; i++) {
            char value = pop_stack(from);
            push_to_stack(to, value);
        }
    }
    
}

void print_top(Stack *stacks[]) {
    for (int i = 0; i < CRATE_COUNT; i++) {
        printf("Crate %d top item: %c\n", i + 1, pop_stack(stacks[i]));
    }
}

void print_crates(Stack *stacks[]) {
    for (int i = 0; i < CRATE_COUNT; i++) {
        printf("Stack %d: ", i + 1);
        for (int j = 0; j <= stacks[i]->top; j++) {
            printf("%c ", stacks[i]->array[j]);
        }

        printf("\n");
    }

    puts("---");
}

void parse_crates(FILE *file, Stack *crates[]) {
    char crate_items[CRATE_COUNT][32];
    memset(crate_items, 0, sizeof(char) * CRATE_COUNT * 32);

    char line[128] = "";
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        char items[3];
        int crate_index = 0;

        if (line[1] == '1') continue;
        if (strcmp(line, "\n") == 0) {
            break;
        }

        for(int j = 1; crate_index < CRATE_COUNT; j += 4) {
            if (line[j] != ' ') {
                crate_items[crate_index][count] = line[j];
            } 

            crate_index++;
        }

        count++;        
    }
    
    for (int i = 0; i < CRATE_COUNT; i++) {
        for (int j = count - 1; j >= 0; j--) {
            char value = crate_items[i][j];
            if (value != 0) push_to_stack(crates[i], value);
        }
    }
}

void move_items(FILE *file, Stack *crates[]) {
    char line[128] = "";
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);

        int move_count, from_index, to_index;
        sscanf(line, "move %d from %d to %d", &move_count, &from_index, &to_index);

        shift(crates[from_index - 1], crates[to_index - 1], move_count, PRESERVE_ORDER);
        print_crates(crates);
    }    
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    Stack *crates[CRATE_COUNT];
    for (int i = 0; i < CRATE_COUNT; i++) {
        crates[i] = new_stack();
    }

    parse_crates(file, crates);
    print_crates(crates);

    move_items(file, crates);
    print_top(crates);

    fclose(file);
    for (int i = 0; i < CRATE_COUNT; i++) {
        free(crates[i]);
    }

    return 0;
}
