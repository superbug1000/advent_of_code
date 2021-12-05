#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define DRAW_COUNT 100
#define CELL_COUNT 5

typedef struct {
   int *matrix[CELL_COUNT][CELL_COUNT]; 
   bool bingo;
} Board;

typedef struct {
    Board *boards;
    uint32_t size;
    uint32_t position;
} BoardArray;

void new_array(BoardArray *array) {
    array->position = 0;
    array->size = 128;
    array->boards = malloc(array->size * sizeof(Board*));
}

void add_to_array(BoardArray *array, Board board) {
    if (array->position >= array->size) {
        array->size *= 2;
        array->boards = realloc(array->boards, array->size * sizeof(Board*));
    }

    array->boards[array->position++] = board;
}

void free_array(BoardArray *array) {
    free(array->boards);
    array->boards = NULL;
}

char** split_string(char* string, char* delimiter, u_int8_t count) {
    char **strings = malloc(sizeof(char*) * count);

    char *token = strtok(string, delimiter);
    for (int i = 0; token != NULL && i < count; i++){
        strings[i] = malloc(sizeof(char) * 2);
        strcpy(strings[i], token);
        token = strtok(NULL, delimiter);
    }

    return strings;
}

void free_strings(char **strings, int size) {
    for(int i = 0; i < size; i++) {
        free(*(strings + i));
    }

    free(strings);
}

void get_drawn_numbers(char* line, int draws[DRAW_COUNT], int drawSet[DRAW_COUNT]) {
    char **strings = split_string(line, ",", DRAW_COUNT);
    for (int j = 0; j < DRAW_COUNT; j++) {
        int value;
        sscanf(strings[j], "%d", &value);

        draws[j] = value;
        drawSet[value] = value;
    }

    free_strings(strings, DRAW_COUNT);
}

void fill_boards(BoardArray *boards, char lines[1000][500], int lines_count, int drawSet[DRAW_COUNT]) {
    for(int i = 2; i < lines_count; i += CELL_COUNT + 1) {
        Board board;
        for (int j = 0; j < CELL_COUNT; j++) {
            char** rowValues = split_string(lines[i+j], " ", CELL_COUNT);
            for (int z = 0; z < CELL_COUNT; z++) {
                int value;
                sscanf(rowValues[z], "%d", &value);

                board.matrix[j][z] = &drawSet[value];
            }

            free_strings(rowValues, CELL_COUNT);
        }

        add_to_array(boards, board);
    }
}

void print_boards(BoardArray *boards) {
    for (int i = 0; i < boards->position; i++) {
        printf("\nBoard %d:\n", i);
        for (int j = 0; j < CELL_COUNT; j++) {
            for (int z = 0; z < CELL_COUNT; z++) {
                printf("%d ", *boards->boards[i].matrix[j][z]);
            }
            printf("\n");
        }
    }
}

bool is_winning_board(int *matrix[CELL_COUNT][CELL_COUNT]) {
    for (int i = 0; i < CELL_COUNT; i++) {
        int result = *matrix[i][0] + *matrix[i][1] + *matrix[i][2] + *matrix[i][3] + *matrix[i][4];
        if (result == -5) {
            return true;
        }

        result = *matrix[0][i] + *matrix[1][i] + *matrix[2][i] + *matrix[3][i] + *matrix[4][i];
        if (result == -5) {
            return true;
        }
    }
    
    return false;
}

int calculate_board_score(int *matrix[CELL_COUNT][CELL_COUNT]) {
    int score = 0;
    for (int i = 0; i < CELL_COUNT; i++) {
        for (int j = 0; j < CELL_COUNT; j++) {
            int value = *matrix[i][j];
            if (value > 0) score += value;
        }
    }

    return score;
}

int check_boards(BoardArray *boards) {
    int totalScore = 0;
    bool anyBingo = false;
    for (int i = 0; i < boards->position; i++) {
        Board *board = &boards->boards[i];
        if (board->bingo) {
            continue;
        }

        if(is_winning_board(board->matrix)) {
            anyBingo = true;
            board->bingo = true;
            totalScore += calculate_board_score(board->matrix);
        }
    }

    return anyBingo ? totalScore : -1;
}

void draw_numbers(int draws[DRAW_COUNT], int drawSet[DRAW_COUNT], BoardArray *boards) {
    for (int i = 0; i < DRAW_COUNT; i++) {
        int calledNumber = draws[i];
        printf("Number %d called!\n", calledNumber);

        drawSet[calledNumber] = -1;
        if (i >= 4) {
            int result = check_boards(boards);
            if (result >= 0) {
                printf("Bingo! Score: %d\n\n", result * calledNumber);
            }
        }
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int lines_count = 0;
    char lines[650][500];
    for(; fgets(lines[lines_count], sizeof(lines[lines_count]), file); lines_count++);
    fclose(file);

    int draws[DRAW_COUNT] = {0};
    int drawSet[DRAW_COUNT] = {0};
    get_drawn_numbers(lines[0], draws, drawSet);

    BoardArray *boards = malloc(sizeof(BoardArray*));
    new_array(boards);
    fill_boards(boards, lines, lines_count, drawSet);

    draw_numbers(draws, drawSet, boards);

    free_array(boards);
    return 0;
}