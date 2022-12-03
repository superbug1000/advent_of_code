#include "stdio.h"
#include <string.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    u_int8_t bucket_size = 128;
    u_int8_t bucket[bucket_size];
    u_int8_t bucket_checked[bucket_size];
    memset(bucket, 0, sizeof(u_int8_t) * bucket_size);
    memset(bucket_checked, 0, sizeof(u_int8_t) * bucket_size);

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

        memset(bucket, 0, sizeof(u_int8_t) * bucket_size);
        memset(bucket_checked, 0, sizeof(u_int8_t) * bucket_size);
    }
    
    printf("Score %d", score);
    
    fclose(file);
    return 0;
}
