#include "stdio.h"
#include <string.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return 1;
    }
    
    int encapsulated_pairs = 0;
    int overlapping_pairs = 0;
    char line[64] = "";
    while (fgets(line, sizeof(line), file))
    {
        int min1, max1, min2, max2;
        sscanf(line, "%d-%d,%d-%d", &min1, &max1, &min2, &max2);

        if ((min1 <= min2 && max1 >= max2) || (min2 <= min1 && max2 >= max1)) 
        {
            encapsulated_pairs++;
        }

        if (max1 >= min2 && max2 >= min1) overlapping_pairs++;
    }

    printf("Encapsulated pairs %d", encapsulated_pairs);
    printf("Overlapping pairs %d", overlapping_pairs);
    
    fclose(file);
    return 0;
}
