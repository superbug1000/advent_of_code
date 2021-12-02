#include "stdio.h"
#include "string.h"

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int x = 0;
    int y1 = 0;
    int y2 = 0;
    
    char line[32] = "";
    while(fgets(line, sizeof(line), file)) {
        char command[32] = "";
        int movement;
        sscanf(line, "%s %d", command, &movement);

        if (strcmp(command, "forward") == 0) {
            x += movement;
            y2 += y1 * movement;
        } else if (strcmp(command, "up") == 0) {
            y1 -= movement;
        } else if (strcmp(command, "down") == 0) {
            y1 += movement;
        } else {
            return 1;
        }
    }

    printf("Part1 -> Sumbarine position X:%d Y:%d Mul: %d\n", x, y1, x * y1);
    printf("Part2 -> Sumbarine position X:%d Y:%d Mul: %d\n", x, y2, x * y2);
    
    fclose(file);
    return 0;
}