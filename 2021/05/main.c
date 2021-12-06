#include "stdio.h"
#include "stdbool.h"

#define BOUNDS 1000

typedef struct {
    unsigned x1;
    unsigned x2;
    unsigned y1;
    unsigned y2;
} Coords;

void draw_line(Coords coords, int world[BOUNDS][BOUNDS]) {
    bool xMov = coords.x2 - coords.x1 != 0;

    int min, max;
    if (xMov > 0) {
        min = coords.x1 < coords.x2 ? coords.x1 : coords.x2;
        max = coords.x1 > coords.x2 ? coords.x1 : coords.x2;
    } else {
        min = coords.y1 < coords.y2 ? coords.y1 : coords.y2;
        max = coords.y1 > coords.y2 ? coords.y1 : coords.y2;
    }

    for (int i = min; i <= max; i++) {
        int xIndex = xMov ? i : coords.x1;
        int yIndex = !xMov ? i : coords.y1;

        world[yIndex][xIndex]++;
    }  
}

void draw_diagonal_line(Coords coords, int world[BOUNDS][BOUNDS]) {
    int yMov = coords.y2 > coords.y1 ? 1 : -1;
    if (coords.x1 < coords.x2) {
        for (int x = coords.x1; x <= coords.x2; x++) {
            int y = coords.y1 + (x - coords.x1) * yMov;
            world[y][x]++;
        }
    } else {
        for (int x = coords.x1; x >= coords.x2; x--) {
            int y = coords.y1 + (coords.x1 - x) * yMov;
            world[y][x]++;
        }
    }
}

void check_world(int world[BOUNDS][BOUNDS]) {
    int count = 0;
    for (int y = 0; y < BOUNDS; y++) {
        for (int x = 0; x < BOUNDS; x++) {
            if (world[y][x] > 1) count++;
        }
    }

    printf("At least 2 lines converge at %d points.\n", count);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int world[BOUNDS][BOUNDS] = { 0 };
    char line[64] = "";
    for(int i = 0; fgets(line, sizeof(line), file); i++) {
        int x1, y1, x2, y2;
        sscanf(line, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

        Coords coords = (Coords) {
            .x1 = x1,
            .y1 = y1,
            .x2 = x2,
            .y2 = y2
        };

        if (x1 == x2 || y1 == y2) {
            draw_line(coords, world);
        } else {
            draw_diagonal_line(coords, world);
        }
    }

    check_world(world);
}