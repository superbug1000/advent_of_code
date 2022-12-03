#include "stdio.h"
#include <string.h>

#define BUCKET_SIZE 128
#define BIT_MASK 7

int part1(FILE *file)
{
    u_int8_t bucket[BUCKET_SIZE];
    u_int8_t bucket_checked[BUCKET_SIZE];
    memset(bucket, 0, sizeof(u_int8_t) * BUCKET_SIZE);
    memset(bucket_checked, 0, sizeof(u_int8_t) * BUCKET_SIZE);

    int score = 0;
    char line[64] = "";
    while (fgets(line, sizeof(line), file))
    {
        u_int8_t bucket_limit = strlen(line) / 2;
        char *p = line;

        for (int i = 0; *p != 0; i++, p++) 
        {
            if(i < bucket_limit) bucket[*p]++;
            else if (bucket[*p] && !bucket_checked[*p]) 
            {
                bucket_checked[*p]++;

                if (*p > 96) score += *p - 96;
                else score += *p  - 38;
            }
        }

        memset(bucket, 0, sizeof(u_int8_t) * BUCKET_SIZE);
        memset(bucket_checked, 0, sizeof(u_int8_t) * BUCKET_SIZE);
    }

    return score;
}

int calc_priorities(u_int8_t bucket[])
{
    int priorities = 0;
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        if (bucket[i] == BIT_MASK)
        {
            if (i > 96) priorities += i - 96;
            else if (i > 64) priorities += i - 38;
        }
    }

    return priorities;
}

int part2(FILE *file)
{
    u_int8_t bucket[BUCKET_SIZE];
    memset(bucket, 0, sizeof(u_int8_t) * BUCKET_SIZE);

    int priorities = 0;
    char line[64] = "";
    for (int i = 0; fgets(line, sizeof(line), file); i++)
    {
        char *p = line;
        for (; *p != 0; p++) 
        {
            bucket[*p] |= (1 << (i % 3));
        }

        if ((i + 1) % 3 == 0)
        {
            priorities += calc_priorities(bucket);
            memset(bucket, 0, sizeof(u_int8_t) * BUCKET_SIZE);
        }
        
    }

    return priorities;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return 1;
    }
    
    printf("Score %d\n", part1(file));
    
    fseek(file, 0, SEEK_SET);
    printf("Priorities %d\n", part2(file));
    
    fclose(file);
    return 0;
}
