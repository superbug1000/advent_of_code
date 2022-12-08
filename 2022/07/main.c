#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct Directory {
    struct Directory *parent;
    struct Directory *children[128];
    
    int children_count;

    int size;
    int total_size;
} Directory;

Directory *new_directory(Directory *parent) {
    Directory *dir = malloc(sizeof(Directory));
    dir->parent = parent;
    dir->children_count = 0;
    dir->size = 0;
    dir->total_size = 0;

    return dir;
}

Directory* handle_cd_command(char line[], Directory *dir) {
    char *command = line + 2;
    if (strncmp("cd", command, 2) == 0) {
        char *arg = command + 3;
        if (strncmp("..", arg, 2) == 0) {
            dir->parent->total_size += dir->total_size;
            return dir->parent;
        } else if (arg[0] != '/') {
            Directory *sub_dir = new_directory(dir);
            dir->children[dir->children_count++] = sub_dir;
            return sub_dir;
        }
    }

    return dir;
}

int parse_size(char line[]) {
    if (line[0] == 'd') return 0;

    int size;
    sscanf(line, "%d *", &size);
    
    return size;
}

int calc_part1(Directory *dir, int at_most, int size) {
    if (dir->total_size <= at_most) {
        size += dir->total_size;
    }

    for (int i = 0; i < dir->children_count; i++) {
        size = calc_part1(dir->children[i], at_most, size);
    }

    return size;
}

int calc_part2(Directory *dir, int threshold, int size) {
    if (dir->total_size >= threshold && (size == 0 || dir->total_size < size)) {
        size = dir->total_size;
    }

    for (int i = 0; i < dir->children_count; i++) {
        size = calc_part2(dir->children[i], threshold, size);
    }

    return size;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }

    Directory *root = new_directory(NULL);
    Directory *dir = root;

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '$') {
            dir = handle_cd_command(line, dir);
        } else {
            int size = parse_size(line);
            dir->size += size;
            dir->total_size += size;
        }
    }

    while(dir->parent != NULL) {
        dir->parent->total_size += dir->total_size;
        dir = dir->parent;
    }

    int size = calc_part1(root, 100000, 0);
    printf("%d\n", size);

    int left = 70000000 - root->total_size;
    int threshold = 30000000 - left;

    size = calc_part2(root, threshold, 0);
    printf("%d\n", size);

    fclose(file);
    return 0;
}
