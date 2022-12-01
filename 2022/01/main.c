#include "stdio.h"
#include <string.h>

#define TOP_COUNT 3

void shift(int max_calories[], int pos)
{
    int prev = max_calories[pos];
    for (int i = pos; i > 0; i--) 
    {
        int tmp = max_calories[i - 1];
        max_calories[i - 1] = prev;
        prev = tmp;
    }
}

void store_max(int max_calories[], int value)
{
    for (int i = TOP_COUNT - 1; i >= 0; i--) 
    {
        if (value > max_calories[i])
        {
            if (max_calories[i] > 0) shift(max_calories, i);

            max_calories[i] = value;
            break;
        }
    }
}

int count_sum(int max_calories[])
{
    int sum = 0;
    for (int i = 0; i < TOP_COUNT; i++) 
    {
        sum += max_calories[i];
    }

    return sum;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    int max_calories[TOP_COUNT];
    memset(max_calories, 0, sizeof(int) * TOP_COUNT);

    int calories_count = 0;
    char line[16] = "";
    while (fgets(line, sizeof(line), file))
    {
        if (*line == '\n')
        {
            store_max(max_calories, calories_count);
            calories_count = 0;
        }
        else
        {
            int value;
            sscanf(line, "%d", &value);
            calories_count += value;
        }
    }

    if (calories_count > 0) store_max(max_calories, calories_count);

    printf("The top %d calories carried were %d!\n", TOP_COUNT, count_sum(max_calories));
    
    fclose(file);
    return 0;
}
